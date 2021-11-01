﻿#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>

using std::string;
using std::vector;
using std::map;


// Terms and nonTerms - nonTerms are all caps(except for prime 'p'), terms are all lower
// Book Parts
 string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "TERM", "TERMp", "FACTOR" };
 string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num" };

// Modified Parts
//string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "LTERM", "LTERMp", "RTERM", "RTERMp", "GFACTOR", "POSVAL", "SPACENEGVAL", "FACTOR" };
//string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num", "negname", "negnum", "spacenegname", "spacenegnum" };


vector<string> readInFile(string filePath) {
	vector<string> lines;
	std::ifstream file;
	file.open(filePath, std::ios::out);
	if (!file) {
		// File coun't open
		std::cout << "Couldn't file file " << filePath;
	}
	else {
		string line;
		while (getline(file, line))
			lines.push_back(line);

		file.close();
	}
	return lines;
}

vector<vector<string>> createProductionTable() {
	vector<vector<string>> productionTable;

	// Insert productions into structure

	// Book Table
	productionTable.push_back({ "EXPR" });
	productionTable.push_back({ "TERM", "EXPRp" });
	productionTable.push_back({ "+", "TERM", "EXPRp" });
	productionTable.push_back({ "-", "TERM", "EXPRp" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "FACTOR", "TERMp" });
	productionTable.push_back({ "*", "FACTOR", "TERMp" });
	productionTable.push_back({ "/", "FACTOR", "TERMp" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "(", "EXPR", ")" });
	productionTable.push_back({ "num" });
	productionTable.push_back({ "name" });

		
	// Modified Version
	//productionTable.push_back({ "EXPR" });				// 0.   Goal ->Expr
	//productionTable.push_back({ "LTERM", "EXPRp" });		// 1.   Expr ->LTerm Expr’
	//productionTable.push_back({ "LFACTOR", "TERMp" });	// 2.   LTerm->LFactor Term’
	//productionTable.push_back({ "LFACTOR", "TERMp" });	// 3.   RTerm->RFactor Term’
	//productionTable.push_back({ "+", "RTERM", "EXPRp" });	// 4.   Expr’-> + RTerm Expr’
	//productionTable.push_back({ "-", "RTERM", "EXPRp" });	// 5.         | - RTerm Expr’
	//productionTable.push_back({ "*", "RTERM", "EXPRp" });	// 7.   Term’-> * RTerm Expr’
	//productionTable.push_back({ "/", "RTERM", "EXPRp" });	// 8.         | / RTerm Expr’
	//productionTable.push_back({ "GFACTOR" });				// 10. LFactor->GFactor
	//productionTable.push_back({ "negnum" });				// 11.        | negnum    //negative val without space only left term 
	//productionTable.push_back({ "negname" });				// 12.        | negname   //negative name without space only left term 
	//productionTable.push_back({ "GFACTOR" });				// 13. RFactor->GFactor
	//productionTable.push_back({ "(", "EXPR", ")" });		// 14. GFactor-> (Expr)
	//productionTable.push_back({ "POSVAL" });				// 15.        | PosVal
	//productionTable.push_back({ "SPACENEGVAL" });			// 16.        | SpaceNegVal
	//productionTable.push_back({ "num" });					// 17. PosVal->num
	//productionTable.push_back({ "name" });				// 18.        | name
	//productionTable.push_back({ "spacenegnum" });			// 19. SpaceNegVal->spacenegnum
	//productionTable.push_back({ "spacenegname" });		// 20.        | spacenegname

	return productionTable;
}

map<string, string> first(vector<vector<string>> productionTable) {
	// https://japp.io/compiler-design/first-and-follow-program-for-cfg-in-c-c/
	// https://github.com/shivam2296/First-and-Follow/blob/master/first%26follow.cpp
	map<string, string> firstTable;

	for (string term : terminals)
		firstTable[term] = term;

	for (string nonTerm : nonTerminals)
		firstTable[nonTerm] = "";

	bool hasChanged = true;
	while (hasChanged) {
		hasChanged = false;
		for (vector<string> production : productionTable) {
			// TODO: Maybe if statement here?
			vector<string> rhs;
			rhs.push_back(firstTable[production[0]]);
			int i = 1;
			for (i; i <= production.size() && firstTable[production[i]] == "e"; i++) {
				for (int j = 0; j < firstTable[production[i]].size(); j++) {
					if (firstTable[production[i + 1]] != "e")
						rhs.push_back(firstTable[production[i + 1]]); // TODO: is this right?
				}
			}

			if (std::find(production.front(), production.back(), "e") != production.back()){
				rhs.push_back("e");			
			}

			map<string, string>& firstTableCopy = firstTable;
			firstTable.insert(std::begin(rhs), std::end(rhs));
			hasChanged |= (firstTableCopy.size() != firstTable.size());
		}

	}

	return firstTable;
}

map<string, string> follow(vector<vector<string>> productionTable, map<string, string> firstTable) {
	map<string, string> followTable;


	//	for each A ∈ N T do;
	//	FOLLOW(A) ← ∅;
	//	end;
	for (string nonTerm : nonTerminals) {
		followTable[nonTerm] = '\0';
	}

	//	FOLLOW(S) ← { eof };
	followTable["S"] = "eof";
	vector<string> trailer;

	//	while (FOLLOW sets are still changing) do;
	bool hasChanged = true;
	while(hasChanged) {

		//	for each p ∈ P of the form A→β1β2 ···βk do;
		for(vector<string> production : productionTable) {
			//	TRAILER ← FOLLOW(A);
			trailer.insert(std::end(trailer), std::begin(production), std::end(production));

			//	for i ← k down to 1 do;
			for (int i = production.size(); i >= 0; i--) {
				
				//	if βi ∈ N T then begin;
				if (std::find(std::begin(nonTerminals), std::end(nonTerminals), production[i]) != std::end(nonTerminals)) {

					//	FOLLOW(βi) ← FOLLOW(βi) ∪ TRAILER;
					followTable[production[i]].insert(std::end(followTable[production[i]]), std::begin(trailer), std::end(trailer));
					// followTable[production[i]] = followTable[production[i]] + trailer; // TODO: add vector onto map?
				}

				if (production[i] == "e") {
					//	if  ∈ FIRST(βi)
					//		then TRAILER ← TRAILER ∪(FIRST(βi) − );
					for (string part : production) {
						if (firstTable[production[i]] != "e")
						trailer.push_back(firstTable[part]);
					}

				} else {
					//	else TRAILER ← FIRST(βi);
					trailer.clear();
					trailer.push_back(firstTable[production[i]]);
				
				}
				
			}
			
			map<string, string>& tableCopy = followTable;
			followTable.insert(std::begin(trailer), std::end(trailer));
			hasChanged |= (tableCopy.size() != followTable.size());
		}
	}

	//  is {βi}
	//end;
	//end;
	//end;
	return followTable;
}

map<string, string> firstPlus(map<string, string> firstTable, map<string, string> followTable) {
	// if e in first() then first()
	// if (std::find(std::begin(firstTable), std::end(firstTable), "e") != std::end(firstTable))
	// 	return firstTable;

	// else first() and follow()
	if (std::find(std::begin(firstTable), std::end(firstTable), "e") == std::end(firstTable))
		firstTable.insert(followTable.begin(), followTable.end());
		
	return firstTable;
}

map<string, map<string, int>> createParseTable(vector<vector<string>> productionTable) {

	// Change specific spots to match the book
	map<string, map<string, int>> parseTable;
	
	// Init parseTable to -1
	for (string terminal : terminals) {
		for (string nonTerminal : nonTerminals) {
			parseTable[nonTerminal][terminal] = -1;
		}
	}

	// Book Table - Hard Coded
	/*

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

	*/

	// Algorithm
	//build FIRST, FOLLOW, and FIRST + sets;
	map<string, string> firstTable = first(productionTable);
	map<string, string> followTable = follow(productionTable, firstTable);
	map<string, string> firstPlusTable = firstPlus(firstTable, followTable);

	//for each nonterminal A do;
	for (string nonTerm : nonTerminals) {
		//for each terminal w do;
		for (string term : terminals) {
			//Table[A, w] <- error; // This is done above
		//end;
		}
		//for each production p of the form A->B do;
		for (int i = 0; i < productionTable.size(); i++) { // (vector<string> production : productionTable)
			//for each terminal w in FIRST + (A->B) do;
			for (string term : terminals) {
				//Table[A, w] <- p;
				parseTable[nonTerm][term] = i;
			//end;
			}
			//if eof in FIRST + (A→B)
			if (std::find(std::begin(firstPlusTable), std::end(firstPlusTable), "eof") != std::end(firstPlusTable)) {
				//	then Table[A, eof] <- p;
				parseTable[nonTerm]["eof"] = i;
			}
		//end;
		}
		
	//end;
	}

	

	return parseTable;
}

string getTermType(string word) {
	if (!(std::find(std::begin(terminals), std::end(terminals), word) != std::end(terminals))) {
		if (std::isdigit(word[0])) {

			bool hasDecimal = false;
			for (char letter : word) {
				if (!std::isdigit(letter) && letter != '.') {
					return "error";
				}

				if (letter == '.') {
					if (hasDecimal) 
						return "error";

					hasDecimal = true;
				}
			}

			return "num";
		}
		else {

			for (char letter : word) {
				if (letter == '.')
					return "error";
			}

			return "name";
		}
	}

	return word;
}

string nextWord(string& line) {
	char keyTerms[] = { '+', '-', '*', '/', '(', ')', '^'};
	string word = "";
	bool finished = false;

	if (line.size() > 0 && !finished) {
		word += line[0];

		for (char term : keyTerms) {
			if (word[0] == term) {
				finished = true;
				break;
			}
		}

		for (int i = 1; i < line.length() && !finished; i++) {
			if (line[i] == ' ' && line[i - 1] != ' ')
				break;

			for (char term : keyTerms) {

				if (line[i] == term) {
					finished = true;

					bool isAllSpace = true;
					for (char letter : word) {
						if (letter != ' ') {
							isAllSpace = false;
							break;
						}
					}

					if (isAllSpace)
						word += line[i];

					break;
				}
			}
			if (!finished)
				word += line[i];
		}
	}

	line.erase(0, word.size());

	while (word[0] == ' ') {
		word.erase(0, 1);
	}
	// TODO: add in negatives

	if (word == "")
		word = "eof";

	return word;
}

int checkLine(vector<vector<string>> productionTable, map<string, map<string, int>> parseTable, string line) {
	vector<string> stack;
	string focus;

	string word = nextWord(line);
	stack.push_back("eof");
	stack.push_back("S");
	focus = stack.back();


	while (true) {
		if (focus == "eof" && word == "eof") {
			// then report successand exit the loop;
			return 1;
		}
		else if ((std::find(std::begin(terminals), std::end(terminals), focus) != std::end(terminals)) || focus == "eof") {
			if (focus == getTermType(word)) {
				stack.pop_back();
				word = nextWord(line);
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
		focus = stack.back();
	}
}

int main()
{
	// Read in files 
	vector<string> file = readInFile("./valid.txt");

	// Create structures for the algorithm
	vector<vector<string>> productionTable = createProductionTable();
	map<string, map<string, int>> parseTable = createParseTable(productionTable);

	for (string line : file) {
		string passedStr = "invalid";

		// Perform the algorithm
		if (checkLine(productionTable, parseTable, line))
			passedStr = "valid";

		std::cout << "(" << passedStr << "): " << line << "\n";
	}

	return 0;
}

