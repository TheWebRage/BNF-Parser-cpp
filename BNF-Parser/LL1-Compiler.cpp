﻿#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>

#include "constants.cpp"
#include "helpers.cpp"
#include "scanner.cpp"
#include "LL1.cpp"
#include "IR.cpp"
#include "asm.cpp"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::cout;
using std::ofstream;


bool checkLine(vector<vector<string>> productionTable, map<string, map<string, int>> parseTable, string line, Node*& root, variable& var, vector<variable>& variables) {
	vector<string> stack;
	string focus;
	Node* focusNode = root;
	vector<int> depthStack;

	bool isNegVal = true;
	string word = nextWord(line, isNegVal);
	if (line[0] == ' ')
		line.erase(0, 1);
	line.erase(0, word.size());
	stack.push_back("eof");
	stack.push_back("GOAL");
	focus = stack.back();

	while (true) {

		if (focus == "eof" && word == "eof") {
			// then report successand exit the loop;
			return 1; // TODO: return the actual end value of the stack
		}
		else if (isTerminal(focus) || focus == "eof") {
			if (focus == getTermType(word)) {
				stack.pop_back();

				// If type declaring for a variable
				if (stack.back() == "VARTYPEAFTER") {
					var.type = word;
				}
				else if (word == "procedure" || word == "return") {
					var.type = word;
				}
				else if (stack.back() == "LINEVARNAMEREMAINING") {
					for (variable varLook : variables) {
						if (varLook.name == word)
							return 0; // Duplicate variable name error
					}
					var.name = word;
				}

				// If not elipson
				else if (word != "e" && word != "=" && word != "(" && word != ")" && word != "{" && word != "}" && word != ",") {
					addToTree(root, focusNode, word, variables);
				}

				// Create Empty Node on tree
				if (isRONT(stack.back())) {
					focusNode->child2 = new Node();
					focusNode->child2->parent = focusNode;
					focusNode = focusNode->child2;

					depthStack.push_back(stack.size());
				}

				// If word is name for variable

				word = nextWord(line, isNegVal);
				if (line[0] == ' ')
					line.erase(0, 1);

				line.erase(0, word.size());

				while (word[0] == ' ')
					word.erase(0, 1);

			}
			else {
				// else report an error looking for symbol at top of stack;
				return 0;
			}
		}
		else {
			try {
				// focus is a nonterminal
				string termType = getTermType(word);
				int productionNum = parseTable[focus][termType];

				if (productionNum == -1 || termType == "error")
					return 0;

				vector<string> curProduction = productionTable[productionNum];

				if (!curProduction.empty()) {
					if (stack.back() == curProduction.front())
						return 0;

					// If consuming a RONT, move up the tree
					if (stack.size() > 0 && depthStack.size() > 0 && focusNode != nullptr) {
						if (curProduction.front() == "e" && !isOperator(stack.back()) && !isRONT(stack.back())) {
							if (depthStack.back() == stack.size()) {
								depthStack.pop_back();
								focusNode = focusNode->parent;
							}
						}
					}

					stack.pop_back();

					for (int i = curProduction.size() - 1; i >= 0; i--) {
						if (curProduction[i] != "e") {
							stack.push_back(curProduction[i]);
						}
					}

				}
				else {
					// report an error expanding focus;
					return 0;
				}
			}
			catch (int ex) {
				return 0;
			}
		}

		string nameNumList[] = { "name", "num", "spacenegname", "spacenegnum", "negname", "negnum", "(" };
		isNegVal = !isInArray(nameNumList, getTermType(word)) && word != ")"; // lastWordWasANumberVarOrRightparens 

		focus = stack.back();
	}
}

int main()
{
	// Read in files 
	vector<string> file = readInFile("./asm.txt");

	// Create structures for the algorithm
	vector<vector<string>> productionTable = createProductionTable();
	map<string, map<string, int>> parseTable = createParseTable(productionTable);

	// Keep track of the IR
	vector < variable > variables;
	
	bool isProcedure = false;

	// Keeps track of the main body asm output
	string asmBody = "";

	for (string line : file) {
		// Skip lines with comments
		if (line[0] == '/' && line[1] == '/') {
			cout << "\n\n" << line << "\n";
			continue;
		}

		string passedStr = "invalid";
		string errorStr = "";

		// Keeps track of the values in a tree
		Node* root = nullptr;
		variable var;

		// If first word is a print function // TODO: get prints working hacky here

		// TODO: get procedures working here hacky

		// Perform the algorithm
		if (checkLine(productionTable, parseTable, line, root, var, variables)) {
			try {
				passedStr = "valid";

				if (var.type == "procedure" || isProcedure) {
					isProcedure == true;
					// TODO: save vars for procedure here
				} else {

					// Perform Math operation on line using post-order traversal and save into variables
					var.value = performCalc(root, var.type, variables);
					var.root = root;
				}

				// Check to see if the procedure has finished
				if (!line.find_first_not_of(' ') == '}') {
					// TODO: pop procedure stack here
					// - keep track of what is the current procedure by looking at the top of this stack
					isProcedure = false;
				}

				variables.push_back(var);
			}
			catch (std::exception e) {
				passedStr = "invalid";
			}

		}

		cout << "(" << passedStr << "): " << line << "\n";
	}

	cout << "\n\nVariables\n";
	for (variable var : variables) {
		if (var.type == "num")
			cout << var.type << " " << var.name << " = " << (int)var.value << "\n";
		else if (var.type == "ish")
			cout << var.type << " " << var.name << " = " << var.value << "\n";
	}


	// Output to an asm file
	ofstream fileO;
	fileO.open("./output/output.asm");
	fileO << startFile(variables) + asmBody;
	fileO.close();


	return 0;
}

