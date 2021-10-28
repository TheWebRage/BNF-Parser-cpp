#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>

using std::string;
using std::vector;
using std::map;


// Terms and nonTerms - nonTerms are all caps(except for prime 'p'), terms are all lower
string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "TERM", "TERMp", "FACTOR" };
string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num" };


vector<vector<string>> createProductionTable() {
	vector<vector<string>> productionTable;

	// Insert productions into structure
	productionTable[0] = { "EXPR" };
	productionTable[1] = { "TERM", "EXPRp" };
	productionTable[2] = { "+", "TERM", "EXPRp" };
	productionTable[3] = { "-", "TERM", "EXPRp" };
	productionTable[4] = { "e" };
	productionTable[5] = { "FACTOR", "TERMp" };
	productionTable[6] = { "*", "FACTOR", "TERMp" };
	productionTable[7] = { "/", "FACTOR", "TERMp" };
	productionTable[8] = { "e" };
	productionTable[9] = { "(", "EXPR", ")" };
	productionTable[10] = { "num" };
	productionTable[11] = { "name" };

	return productionTable;
}

map<string, map<string, int>> createParseTable() {

	// Change specific spots to match the book
	map<string, map<string, int>> parseTable;
	
	// Init parseTable to -1
	for (string terminal : terminals) {
		for (string nonTerminal : nonTerminals) {
			parseTable[nonTerminal][terminal] = -1;
		}
	}

	// Goal
	parseTable["GOAL"]["("] = 0;
	parseTable["GOAL"]["name"] = 0;
	parseTable["GOAL"]["num"] = 0;

	// Expr
	parseTable["EXPR"]["("] = 1;
	parseTable["EXPR"]["name"] = 1;
	parseTable["EXPR"]["num"] = 1;

	// ExprP
	parseTable["EXPRp"]["eof"] = 4;
	parseTable["EXPRp"]["+"] = 2;
	parseTable["EXPRp"]["-"] = 3;
	parseTable["EXPRp"][")"] = 4;

	// Term
	parseTable["TERM"]["("] = 5;
	parseTable["TERM"]["name"] = 5;
	parseTable["TERM"]["num"] = 5;

	// TermP
	parseTable["TERMp"]["eof"] = 8;
	parseTable["TERMp"]["+"] = 8;
	parseTable["TERMp"]["-"] = 8;
	parseTable["TERMp"]["*"] = 6;
	parseTable["TERMp"]["/"] = 7;
	parseTable["TERMp"][")"] = 8;

	// Factor
	parseTable["FACTOR"]["("] = 9;
	parseTable["FACTOR"]["name"] = 11;
	parseTable["FACTOR"]["num"] = 10;

	return parseTable;
}

string nextWord() {
	// TODO: add functionality here
	return "";
}

bool checkLine(vector<vector<string>> productionTable, map<string, map<string, int>> parseTable) {
	vector<string> stack;
	string focus;

	string word = nextWord();
	stack.push_back("eof");
	stack.push_back("S");
	focus = stack.front();

	while (true) {
		if (focus == "eof" && word == "eof") {
			// then report successand exit the loop;
			return true;
		}
		else if ((std::find(std::begin(terminals), std::end(terminals), focus) != std::end(terminals)) || focus == "eof") {
			if (focus == word) {
				stack.pop_back();
				word = nextWord();
			}
			else {
				// else report an error looking for symbol at top of stack;
				return false;
			}
		}
		else {
			// focus is a nonterminal 
			int productionNum = parseTable[focus][word];
			vector<string> curProduction = productionTable[productionNum];

			if (!curProduction.empty()) {
				stack.pop_back();
				for (int i = curProduction.size() - 1; i >= 0; i--) {
					if (curProduction[i] != "e") {
						stack.push_back(curProduction[i]);
					}
				}

			}
			else {
				// report an error expanding focus;
				return false;
			}
		}
		focus = stack.front();
	}
}

int main()
{
	// Read in files 
	// TODO: read in files

	// Create structures for the algorithm
	vector<vector<string>> productionTable = createProductionTable();
	map<string, map<string, int>> parseTable = createParseTable();

	// TODO: for each line in file
	// Perform the algorithm
	checkLine(productionTable, parseTable);
	// TODO: print result to user;

	return 0;
}

