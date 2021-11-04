#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <regex>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

// Terms and nonTerms - nonTerms are all caps(except for prime 'p'), terms are all lower
// Book Parts
//string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "TERM", "TERMp", "FACTOR" };
//string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num" };

// Modified Parts
string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "LTERM", "RTERM", "TERMp", "LFACTOR", "RFACTOR", "GFACTOR", "POSVAL", "SPACENEGVAL" };
string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num", "negname", "negnum", "spacenegname", "spacenegnum" };


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
	//productionTable.push_back({ "EXPR" });
	//productionTable.push_back({ "TERM", "EXPRp" });
	//productionTable.push_back({ "+", "TERM", "EXPRp" });
	//productionTable.push_back({ "-", "TERM", "EXPRp" });
	//productionTable.push_back({ "e" });
	//productionTable.push_back({ "FACTOR", "TERMp" });
	//productionTable.push_back({ "*", "FACTOR", "TERMp" });
	//productionTable.push_back({ "/", "FACTOR", "TERMp" });
	//productionTable.push_back({ "e" });
	//productionTable.push_back({ "(", "EXPR", ")" });
	//productionTable.push_back({ "num" });
	//productionTable.push_back({ "name" });


	// Modified Version
	productionTable.push_back({ "EXPR" });					// 0.   Goal ->Expr
	productionTable.push_back({ "LTERM", "EXPRp" });		// 1.   Expr ->LTerm Expr’
	productionTable.push_back({ "LFACTOR", "TERMp" });		// 2.   LTerm->LFactor Term’
	productionTable.push_back({ "RFACTOR", "TERMp" });		// 3.   RTerm->RFactor Term’
	productionTable.push_back({ "+", "RTERM", "EXPRp" });	// 4.   Expr’-> + RTerm Expr’
	productionTable.push_back({ "-", "RTERM", "EXPRp" });	// 5.         | - RTerm Expr’
	productionTable.push_back({ "e" });						// 6.         | e
	productionTable.push_back({ "*", "RTERM", "TERMp" });	// 7.   Term’-> * RTerm Term’
	productionTable.push_back({ "/", "RTERM", "TERMp" });	// 8.         | / RTerm Term’
	productionTable.push_back({ "^", "RTERM", "TERMp" });	// 9 .        | ^ RTerm Expo`
	productionTable.push_back({ "e" });						// 10.        | e
	productionTable.push_back({ "GFACTOR" });				// 11. LFactor->GFactor
	productionTable.push_back({ "negnum" });				// 12.        | negnum    //negative val without space only left term 
	productionTable.push_back({ "negname" });				// 13.        | negname   //negative name without space only left term 
	productionTable.push_back({ "GFACTOR" });				// 14. RFactor->GFactor
	productionTable.push_back({ "(", "EXPR", ")" });		// 15. GFactor-> (Expr)
	productionTable.push_back({ "POSVAL" });				// 16.        | PosVal
	productionTable.push_back({ "SPACENEGVAL" });			// 17.        | SpaceNegVal
	productionTable.push_back({ "num" });					// 18. PosVal->num
	productionTable.push_back({ "name" });					// 19.        | name
	productionTable.push_back({ "spacenegnum" });			// 20. SpaceNegVal->spacenegnum
	productionTable.push_back({ "spacenegname" });			// 21.        | spacenegname

	return productionTable;
}

string getTerm(int productionNum) {
	switch (productionNum) {
		//case 0:
		//	return "GOAL";
		//case 1:
		//	return "EXPR";
		//case 2:
		//	return "EXPRp";
		//case 3:
		//	return "EXPRp";
		//case 4:
		//	return "EXPRp";
		//case 5:
		//	return "TERM";
		//case 6:
		//	return "TERMp";
		//case 7:
		//	return "TERMp";
		//case 8:
		//	return "TERMp";
		//case 9:
		//	return "FACTOR";
		//case 10:
		//	return "FACTOR";
		//case 11:
		//	return "FACTOR";

	case 0:
		return "GOAL";				// 0.   Goal ->Expr
	case 1:
		return "EXPR";				// 1.   Expr ->LTerm Expr’
	case 2:
		return "LTERM";				// 2.   LTerm->LFactor Term’			
	case 3:
		return "RTERM";			// 3.   RTerm->RFactor Term’			
	case 4:
		return "EXPRp";			// 4.   Expr’-> + RTerm Expr’			
	case 5:
		return "EXPRp";			// 5.         | - RTerm Expr’			
	case 6:
		return "EXPRp";			// 6.         | e			
	case 7:
		return "TERMp";			// 7.   Term’-> * RTerm Term’	
	case 8:
		return "TERMp";			// 8.         | / RTerm Term’
	case 9:
		return "TERMp";			// 9.         | e
	case 10:
		return "TERMp";
	case 11:
		return "LFACTOR";			// 10. LFactor->GFactor
	case 12:
		return "LFACTOR";			// 11.        | negnum    //negative val without space only left term 	
	case 13:
		return "LFACTOR";			// 12.        | negname   //negative name without space only left term	
	case 14:
		return "RFACTOR";			// 13. RFactor->GFactor	
	case 15:
		return "GFACTOR";			// 14. GFactor-> (Expr)
	case 16:
		return "GFACTOR";			// 15.        | PosVal
	case 17:
		return "GFACTOR";			// 16.        | SpaceNegVal
	case 18:
		return "POSVAL";			// 17. POSVAL -> | num
	case 19:
		return "POSVAL";			// 18.           | name
	case 20:
		return "SPACENEGVAL";		// 19. SpaceNegVal->spacenegnum
	case 21:
		return "SPACENEGVAL";		// 20.        | spacenegname
	}

	return "";
}

int getNonTermStart(string term, vector<vector<string>> productionTable) {
	for (int i = 0; i < productionTable.size(); i++) {
		if (getTerm(i) == term)
			return i;
	}
	return 0;
}

bool isNonTerminal(string term) {
	for (string nonTerm : nonTerminals) {
		if (term == nonTerm)
			return true;
	}
	return false;
}

bool isTerminal(string term) {
	for (string terms : terminals) {
		if (term == terms)
			return true;
	}
	return false;
}

bool isInVector(vector<string> set1, string itemInSet) {
	for (string item : set1) {
		if (itemInSet == item)
			return true;
	}
	return false;
}

bool isInArray(string set1, char itemInSet) {
	for (char item : set1) {
		if (itemInSet == item)
			return true;
	}
	return false;
}

bool isInArray(string set1[], string itemInSet) {
	for (int i = 0; i < set1->size(); i++) {
		if (itemInSet == set1[i])
			return true;
	}
	return false;
}

set<string> unionSets(set<string> set1, set<string> set2) {
	set<string> s;
	std::set_union(set1.begin(), set1.end(),
		set2.begin(), set2.end(),
		std::inserter(s, s.begin()));

	return s;
}

set<string> removeElement(set<string> set1, string removeStr) {
	for (auto it = set1.begin(); it != set1.end(); ++it) {
		if (*it == removeStr) {
			set1.erase(it);
			return set1;
		}
	}
	return set1;
}

void first(vector< vector<string> > productionTable, map< string, set<string> >& firstTable) {

	for (string term : terminals) {
		firstTable[term].insert(term);
	}
	for (string nonTerm : nonTerminals) {
		firstTable[nonTerm].clear();
	}

	map<string, set<string>> firstTableCopy = firstTable;
	bool changing = true;

	while (changing) {
		for (int j = 0; j < productionTable.size(); j++) {
			vector<string> production = productionTable[j];
			set<string> rhs = removeElement(firstTable[production[0]], "e");
			int i = 1;

			for (int c = 0; c < production.size(); c++) {
				string part = production[c];
				if (part == "e" && i + 1 <= production.size() - 1) {
					rhs = unionSets(rhs, firstTable[production[i + 1]]); // TODO: fix this
					i++;
				}
			}

			if (production.back() == "e" && production.size() == 1) {
				rhs.insert("e");
			}

			firstTable[getTerm(j)] = unionSets(firstTable[getTerm(j)], rhs);
		}

		if (firstTableCopy == firstTable) {
			changing = false;
		}
		else {
			firstTableCopy = firstTable;
		}
	}

}

void follow(vector< vector<string> > productionTable, map< string, set<string> >& followTable, map< string, set<string> > firstTable) {

	for (string nonTerm : nonTerminals) {
		followTable[nonTerm].clear();
	}

	followTable["GOAL"].insert("eof");

	map<string, set<string>> followTableCopy = followTable;
	bool changing = true;
	while (changing) {
		for (int j = 0; j < productionTable.size(); j++) {
			vector<string> production = productionTable[j];

			set<string> trailer = followTable[getTerm(j)];
			int k = production.size();

			for (int i = k - 1; i >= 0; --i) {
				if (isNonTerminal(production[i])) {
					followTable[production[i]] = unionSets(followTable[production[i]], trailer);

					if (firstTable[production[i]].find("e") != firstTable[production[i]].end()) {
						trailer = unionSets(trailer, removeElement(firstTable[production[i]], "e"));
					}
					else {
						trailer = firstTable[production[i]];
					}

				}
				else {
					trailer = firstTable[production[i]];
				}

			}
		}

		if (followTableCopy == followTable) {
			changing = false;
		}
		else {
			followTableCopy = followTable;
		}
	}

	/*
	//	while (FOLLOW sets are still changing) do;
	//		for each p ∈ P of the form A→β1β2 ···βk do;
	//		TRAILER ← FOLLOW(A);
	//		for i ← k down to 1 do;
	//			if βi ∈ N T then begin;
	//				FOLLOW(βi) ← FOLLOW(βi) ∪ TRAILER;
	//					if e ∈ FIRST(βi)
	//						then TRAILER ← TRAILER ∪(FIRST(βi) − e);
	//					else TRAILER ← FIRST(βi);
	//					end;
	//			else TRAILER ← FIRST(βi); // is {βi}
	//			end;
	//		end;
	//end;
	*/

}

set<string> firstPlus(string productionPart, set<string> firstSet, set<string> followSet) {
	// // if e in first() then first()
	// // else first() and follow()

	if (productionPart == "e") {
		firstSet = unionSets(firstSet, followSet);
	}

	return firstSet;
}

map<string, map<string, int>> createParseTable(vector< vector<string> > productionTable) {

	map<string, map<string, int>> parseTable;

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
	map< string, set<string> > firstTable;
	first(productionTable, firstTable);

	//std::cout << "First:\n";
	//for (string term : terminals) {
	//    std::cout << term << ": ";
	//    for (string item : firstTable[term])
	//        std::cout << item << " ";
	//    
	//    std::cout << "\n";
	//}
	//for (string nonTerm : nonTerminals) {
	//    std::cout << nonTerm << ": ";
	//    for (string item : firstTable[nonTerm])
	//        std::cout << item << " ";
	//    
	//    std::cout << "\n";
	//}

	map< string, set<string> > followTable;
	follow(productionTable, followTable, firstTable);

	//std::cout << "\n\nFollow:\n";
	//for (string term : terminals) {
	//    std::cout << term << ": ";
	//    for (string item : followTable[term])
	//        std::cout << item << " ";
	//    
	//    std::cout << "\n";
	//}
	//for (string nonTerm : nonTerminals) {
	//    std::cout << nonTerm << ": ";
	//    for (string item : followTable[nonTerm])
	//        std::cout << item << " ";
	//    
	//    std::cout << "\n";
	//}

	set<string> firstPlusSet;

	for (string nonTerm : nonTerminals) {
		// Init parseTable to -1
		for (string term : terminals) {
			parseTable[nonTerm][term] = -1;
		}

		for (int j = getNonTermStart(nonTerm, productionTable); j < productionTable.size(); j++) {
			vector<string> production = productionTable[j];

			if (getTerm(j) != nonTerm)
				break;

			firstPlusSet = firstPlus(production[0], firstTable[production[0]], followTable[getTerm(j)]);
			for (string item : firstPlusSet) {
				if (parseTable[getTerm(j)][item] == -1)
					parseTable[getTerm(j)][item] = j;
			}

		}
	}

	/*
	//for each nonterminal A do;
	//	for each terminal w do;
	//		Table[A, w] <- error;
	//	end;
	//	for each production p of the form A->B do;
	//		for each terminal w in FIRST + (A->B) do;
	//			Table[A, w] < -p;
	//		end;
	//		if eof in FIRST + (A→B)
	//			then Table[A, eof] < -p;
	//	end;
	//end;
	*/

	//std::cout << "\n\nParse Table\n";
	//for (string term : terminals) {
	//        std::cout << "\t" << term;
	//    }
	//std::cout << "\n";
	//for (string nonTerm : nonTerminals) {
	//    std::cout << nonTerm << ":";
	//    for (string term : terminals) {
	//        std::cout << "\t" << parseTable[nonTerm][term];
	//    }
	//    std::cout << "\n";
	//}

	return parseTable;
}

string getTermType(string word) {
	if (!(std::find(std::begin(terminals), std::end(terminals), word) != std::end(terminals))) {

		if (std::regex_match(word, std::regex("[0-9]+.?[0-9]*")))
			return "num";

		if (std::regex_match(word, std::regex("[a-z|A-Z]+[a-z|A-Z|0-9|_]*")))
			return "name";

		if (std::regex_match(word, std::regex("\s-[0-9]+.?[0-9]*$")))
			return "regspacenegnum";

		if (std::regex_match(word, std::regex("\s-[a-z|A-Z]+[a-z|A-Z|0-9|_]*")))
			return "regspacenegname";

		if (std::regex_match(word, std::regex("-[0-9]+.?[0-9]*")))
			return "num";

		if (std::regex_match(word, std::regex("-[a-z|A-Z]+[a-z|A-Z|0-9|_]*")))
			return "name";

	}

	if (word == "^") {
		return "*";
	}

	else if (word == ".")
		return "error";

	return word;
}

string nextWord(string line, bool isNegVal = false) {
	/*char keyTerms[] = { '+', '-', '*', '/', '(', ')', '^'};
	string word = "";
	bool finished = false;

	if (line.size() > 0 && !finished) {
		word += line[0];

		bool isTerm = false;
		for (char term : keyTerms) {
			if (word[0] == term && !(word[0] == '-' && isNegVal)) {
				isTerm = true;
				finished = true;
				break;
			}
		}

		//if (!isTerm) {
		//	if (word[0] != ' ') {
		//		isNegVal = false;
		//	}
		//}

		for (int i = 1; i < line.length() && !finished; i++) {
			if (line[i] == ' ' && line[i - 1] != ' ' && !(word[0] == '-' && isNegVal))
				break;

			for (char term : keyTerms) {

				if (line[i] == term) {
					if (line[i] == '-' && isNegVal)
						break;

					finished = true;

					bool isAllSpace = true;
					for (char letter : word) {
						if (letter != ' ') {
							isAllSpace = false;
							break;
						}
					}

					if (isAllSpace) {
						word += line[i];
					}

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

	if (word[0] == '-') {
		word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
	}

	if (word == "")
		word = "eof";

	return word;*/

	// --------------------------------------------------- //

	char keyTerms[] = { '+', '-', '*', '/', '(', ')', '^' };
	string word = "";
	int nonNumspaceChars = 0;
	int numSpaceChars = 0;
	bool hasNegChar = false;

	// Get the next word
	if (line.size() > 0) {
		
		for (int i = 0; i < line.size(); i++) {
			char ch = line[i];
			char nextChar = '\0';

			if (line.size() > i + 1) {
				nextChar = line[i + 1];
			}

			// Compare with KeyTerms
			if (isInArray(keyTerms, ch) && ch != ' ') {
				if (nonNumspaceChars > 0)
					break;

				if (ch == ')')
					return ")";
				if (ch == '(')
					return "(";

				// Negative Logic
				if (ch == '-') {
					if (isNegVal) {
						word += ch;
						nonNumspaceChars++;
						hasNegChar = true;
						continue;
					}
					else {
						return "-";
					}
				}

				if (nonNumspaceChars == 0 && numSpaceChars == 0) {
					line.erase(0, 1);
					std::string s(1, ch);
					return s;
				}
				else {
					if (nextChar == ' ') {
						std::string s(1, ch);
						return s;
					}

					word += ch;
				}
			}
			else if (ch == ' ' && word.size() > 0 && nonNumspaceChars > 0) {
				line.erase(0, word.size());
				break;
			}
			else {
				if (ch != ' ')
					nonNumspaceChars++;
				else
					numSpaceChars++;

				word += ch;
			}
		}

		if (hasNegChar) {
			while (numSpaceChars > 1) {
				word.erase(0, 1);
				numSpaceChars--;
			}
		}
		else {
			if (word[0] == ' ')
				word.erase(0, 1);
		}

		line.erase(0, word.size());

		return word;
	}
	else {
		return "eof";
	}
}

int checkLine(vector<vector<string>> productionTable, map<string, map<string, int>> parseTable, string line) {
	vector<string> stack;
	string focus;

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
			return 1;
		}
		else if ((std::find(std::begin(terminals), std::end(terminals), focus) != std::end(terminals)) || focus == "eof") {
			if (focus == getTermType(word)) {
				stack.pop_back();
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

		string nameNumList[] = { "name", "num", "spacenegname", "spacenegnum", "negname", "negnum", ")" };
		isNegVal = !(isInArray(nameNumList, getTermType(word)) || word == ")");

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

