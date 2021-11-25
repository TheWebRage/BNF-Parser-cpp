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
// string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "TERM", "TERMp", "FACTOR" };
// string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num" };

//// Modified Parts
// string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "LTERM", "RTERM", "TERMp", "LFACTOR", "RFACTOR", "GFACTOR", "POSVAL", "SPACENEGVAL" };
// string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num", "negname", "negnum", "spacenegname", "spacenegnum" };

// IR Version
string nonTerminals[] = { "GOAL", "LINEFULL", "VARTYPEAFTER", "LINEVARNAME", "LINEVARNAMEREMAINING", "PROCEDUREPARAMS", "PARAMS", "MOREPARAMS", "VARTYPE", "EXPR", "LTERMADDSUB", "LTERMMULTDIV", "RTERMMULTDIV", "RTERMADDSUB", "ADDSUBp", "MULTDIVp", "MULTANDRIGHTOP", "DIVANDRIGHTOP", "POWERp", "POWERANDRIGHTOP", "LTERMPOWER", "RTERMPOWER", "GTERM", "PARENS", "POSVAL", "SPACENEGVAL" };
string terminals[] = { "eof", "+", "-", "*", "/", "=", "(", ")", "^", "num", "name", "negnum", "negname", "spacenegnum", "spacenegname", "{", "}", ",", "ish", "result", "procedure", "e" };
string operators[] = { "+", "-", "*", "/", "^" };
string ronts[] = { "RTERMADDSUB", "RTERMMULTDIV", "RTERMPOWER" };

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


	//// Modified Version
	//productionTable.push_back({ "EXPR" });					// 0.   Goal ->Expr
	//productionTable.push_back({ "LTERM", "EXPRp" });		// 1.   Expr ->LTerm Expr’
	//productionTable.push_back({ "LFACTOR", "TERMp" });		// 2.   LTerm->LFactor Term’
	//productionTable.push_back({ "RFACTOR", "TERMp" });		// 3.   RTerm->RFactor Term’
	//productionTable.push_back({ "+", "RTERM", "EXPRp" });	// 4.   Expr’-> + RTerm Expr’
	//productionTable.push_back({ "-", "RTERM", "EXPRp" });	// 5.         | - RTerm Expr’
	//productionTable.push_back({ "e" });						// 6.         | e
	//productionTable.push_back({ "*", "RTERM", "TERMp" });	// 7.   Term’-> * RTerm Term’
	//productionTable.push_back({ "/", "RTERM", "TERMp" });	// 8.         | / RTerm Term’
	//productionTable.push_back({ "^", "RTERM", "TERMp" });	// 9 .        | ^ RTerm Expo`
	//productionTable.push_back({ "e" });						// 10.        | e
	//productionTable.push_back({ "GFACTOR" });				// 11. LFactor->GFactor
	//productionTable.push_back({ "negnum" });				// 12.        | negnum    //negative val without space only left term 
	//productionTable.push_back({ "negname" });				// 13.        | negname   //negative name without space only left term 
	//productionTable.push_back({ "GFACTOR" });				// 14. RFactor->GFactor
	//productionTable.push_back({ "(", "EXPR", ")" });		// 15. GFactor-> (Expr)
	//productionTable.push_back({ "POSVAL" });				// 16.        | PosVal
	//productionTable.push_back({ "SPACENEGVAL" });			// 17.        | SpaceNegVal
	//productionTable.push_back({ "num" });					// 18. PosVal->num
	//productionTable.push_back({ "name" });					// 19.        | name
	//productionTable.push_back({ "spacenegnum" });			// 20. SpaceNegVal->spacenegnum
	//productionTable.push_back({ "spacenegname" });			// 21.        | spacenegname

	// IR Version
	productionTable.push_back({ "LINEFULL" });
	productionTable.push_back({ "VARTYPE", "VARTYPEAFTER" });
	productionTable.push_back({ "LINEVARNAME" });
	productionTable.push_back({ "negnum", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "PARENS", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "result", "GTERM" });
	productionTable.push_back({ "}" });
	productionTable.push_back({ "LINEVARNAME" });
	productionTable.push_back({ "procedure", "name", "PROCEDUREPARAMS", "{" });
	productionTable.push_back({ "name", "LINEVARNAMEREMAINING" });
	productionTable.push_back({ "=", "EXPR" });
	productionTable.push_back({ "POWERANDRIGHTOP", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "MULTANDRIGHTOP", "ADDSUBp" });
	productionTable.push_back({ "DIVANDRIGHTOP", "ADDSUBp" });
	productionTable.push_back({ "ADDSUBp" });
	productionTable.push_back({ "(", "PARAMS", ")" });
	productionTable.push_back({ "VARTYPE", "name", "MOREPARAMS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ ",", "VARTYPE", "name", "MOREPARAMS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "num" });
	productionTable.push_back({ "ish" });
	productionTable.push_back({ "LTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "LTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "LTERMPOWER", "POWERp" });
	productionTable.push_back({ "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "RTERMPOWER", "POWERp" });
	productionTable.push_back({ "+", "RTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "-", "RTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "MULTANDRIGHTOP" });
	productionTable.push_back({ "DIVANDRIGHTOP" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "*", "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "/", "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "POWERANDRIGHTOP" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "^", "RTERMPOWER", "POWERp" });
	productionTable.push_back({ "GTERM" });
	productionTable.push_back({ "negnum" });
	productionTable.push_back({ "negname" });
	productionTable.push_back({ "GTERM" });
	productionTable.push_back({ "PARENS" });
	productionTable.push_back({ "POSVAL" });
	productionTable.push_back({ "SPACENEGVAL" });
	productionTable.push_back({ "(", "EXPR", ")" });
	productionTable.push_back({ "num" });
	productionTable.push_back({ "name" });
	productionTable.push_back({ "spacenegnum" });
	productionTable.push_back({ "spacenegname" });


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

	//case 0:
	//	return "GOAL";				// 0.   Goal ->Expr
	//case 1:
	//	return "EXPR";				// 1.   Expr ->LTerm Expr’
	//case 2:
	//	return "LTERM";				// 2.   LTerm->LFactor Term’			
	//case 3:
	//	return "RTERM";			// 3.   RTerm->RFactor Term’			
	//case 4:
	//	return "EXPRp";			// 4.   Expr’-> + RTerm Expr’			
	//case 5:
	//	return "EXPRp";			// 5.         | - RTerm Expr’			
	//case 6:
	//	return "EXPRp";			// 6.         | e			
	//case 7:
	//	return "TERMp";			// 7.   Term’-> * RTerm Term’	
	//case 8:
	//	return "TERMp";			// 8.         | / RTerm Term’
	//case 9:
	//	return "TERMp";			// 9.         | e
	//case 10:
	//	return "TERMp";
	//case 11:
	//	return "LFACTOR";			// 10. LFactor->GFactor
	//case 12:
	//	return "LFACTOR";			// 11.        | negnum    //negative val without space only left term 	
	//case 13:
	//	return "LFACTOR";			// 12.        | negname   //negative name without space only left term	
	//case 14:
	//	return "RFACTOR";			// 13. RFactor->GFactor	
	//case 15:
	//	return "GFACTOR";			// 14. GFactor-> (Expr)
	//case 16:
	//	return "GFACTOR";			// 15.        | PosVal
	//case 17:
	//	return "GFACTOR";			// 16.        | SpaceNegVal
	//case 18:
	//	return "POSVAL";			// 17. POSVAL -> | num
	//case 19:
	//	return "POSVAL";			// 18.           | name
	//case 20:
	//	return "SPACENEGVAL";		// 19. SpaceNegVal->spacenegnum
	//case 21:
	//	return "SPACENEGVAL";		// 20.        | spacenegname

	case 0:
		return"GOAL";
	case 1:
		return"LINEFULL";
	case 2:
		return"LINEFULL";
	case 3:
		return"LINEFULL";
	case 4:
		return"LINEFULL";
	case 5:
		return"LINEFULL";
	case 6:
		return"LINEFULL";
	case 7:
		return"VARTYPEAFTER";
	case 8:
		return"VARTYPEAFTER";
	case 9:
		return"LINEVARNAME";
	case 10:
		return"LINEVARNAMEREMAINING";
	case 11:
		return"LINEVARNAMEREMAINING";
	case 12:
		return"LINEVARNAMEREMAINING";
	case 13:
		return"LINEVARNAMEREMAINING";
	case 14:
		return"LINEVARNAMEREMAINING";
	case 15:
		return"PROCEDUREPARAMS";
	case 16:
		return"PARAMS";
	case 17:
		return"PARAMS";
	case 18:
		return"MOREPARAMS";
	case 19:
		return"MOREPARAMS";
	case 20:
		return"VARTYPE";
	case 21:
		return"VARTYPE";
	case 22:
		return"EXPR";
	case 23:
		return"LTERMADDSUB";
	case 24:
		return"LTERMMULTDIV";
	case 25:
		return"RTERMADDSUB";
	case 26:
		return"RTERMMULTDIV";
	case 27:
		return"ADDSUBp";
	case 28:
		return"ADDSUBp";
	case 29:
		return"ADDSUBp";
	case 30:
		return"MULTDIVp";
	case 31:
		return"MULTDIVp";
	case 32:
		return"MULTDIVp";
	case 33:
		return"MULTANDRIGHTOP";
	case 34:
		return"DIVANDRIGHTOP";
	case 35:
		return"POWERp";
	case 36:
		return"POWERp";
	case 37:
		return"POWERANDRIGHTOP";
	case 38:
		return"LTERMPOWER";
	case 39:
		return"LTERMPOWER";
	case 40:
		return"LTERMPOWER";
	case 41:
		return"RTERMPOWER";
	case 42:
		return"GTERM";
	case 43:
		return"GTERM";
	case 44:
		return"GTERM";
	case 45:
		return"PARENS";
	case 46:
		return"POSVAL";
	case 47:
		return"POSVAL";
	case 48:
		return"SPACENEGVAL";
	case 49:
		return"SPACENEGVAL";
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

bool isRONT(string term) {
	for (string ront : ronts) {
		if (term == ront)
			return true;
	}
	return false;
}

bool isOperator(string term) {
	for (string operStr : operators) {
		if (term == operStr)
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

bool isAllSpace(string word) {
	return word.find_first_not_of(' ') == std::string::npos;
}

inline bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

void printTable(map< string, set<string> > table, string tableName = "") {
	std::cout << tableName;
	for (string term : terminals) {
		std::cout << term << ": ";
		for (string item : table[term])
			std::cout << item << " ";

		std::cout << "\n";
	}
	for (string nonTerm : nonTerminals) {
		std::cout << nonTerm << ": ";
		for (string item : table[nonTerm])
			std::cout << item << " ";

		std::cout << "\n";
	}
}

void printTable(map<string, map<string, int>> table, string tableName = "") {
	std::cout << tableName;
	for (string term : terminals) {
		std::cout << "\t" << term;
	}
	std::cout << "\n";
	for (string nonTerm : nonTerminals) {
		std::cout << nonTerm << ":";
		for (string term : terminals) {
			std::cout << "\t" << table[nonTerm][term];
		}
		std::cout << "\n";
	}
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
					rhs = unionSets(rhs, firstTable[production[i + 1]]);
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
	// printTable(firstTable, "\n\nFirst:\n");

	map< string, set<string> > followTable;
	follow(productionTable, followTable, firstTable);
	// printTable(followTable, "\n\nFollow:\n");

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

	// printTable(parseTable, "\n\nParseTable:\n");

	return parseTable;
}

string getTermType(string word) {
	if (word == "procedure")
		return word;

	if (!(std::find(std::begin(terminals), std::end(terminals), word) != std::end(terminals))) {

		if (std::regex_match(word, std::regex("[0-9]+.?[0-9]*")))
			return "num";

		if (std::regex_match(word, std::regex("[a-z|A-Z]+[a-z|A-Z|0-9|_]*")))
			return "name";

		if (std::regex_match(word, std::regex("\\s-[0-9]+.?[0-9]*$")))
			return "spacenegnum";

		if (std::regex_match(word, std::regex("\\s-[a-z|A-Z]+[a-z|A-Z|0-9|_]*")))
			return "spacenegname";

		if (std::regex_match(word, std::regex("-[0-9]+.?[0-9]*")))
			return "negnum";

		if (std::regex_match(word, std::regex("-[a-z|A-Z]+[a-z|A-Z|0-9|_]*")))
			return "negname";

	}

	if (word == "^") {
		return "*";
	}

	else if (word == ".")
		return "error";

	return word;
}

string nextWord(string line, bool isNegVal = false) {
	char keyTerms[] = { '+', '-', '*', '/', '(', ')', '^', ','};
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

			// if the character is a terminal (not '-')
			if (isInArray(keyTerms, ch) && ch != '-') {

				// if the string only has spaces, add the char to the word
				if (isAllSpace(word))
				{
					word += ch;
				}

				// End scanning
				break;
			}

			else if (ch == '-') {
				// If the value is not a neg value, stop scanning
				if (!isNegVal) {
					// if the string only has spaces, add the char to the word
					if (isAllSpace(word) || word == "")
					{
						word += ch;
					}
					break;
				}
				else {
					if (isAllSpace(word) || word == "")
					{
						word += ch;
					}
					else {
						break;
					}

				}
			}
			else if (!isAllSpace(word) && ch == ' ') {
				break;
			}
			else {
				word += ch;
			}

		}

		line.erase(0, word.size());

		while (word[0] == ' ') {
			if (word[1] == '-' && word.size() > 2 && isNegVal) {
				break;
			}
			word.erase(0, 1);

		}

		return word;
	}
	else {
		return "eof";
	}
}

class Node {
public:

	string value = "";

	Node* child1;
	Node* child2;

	Node* parent;
};

struct variable {
public:
	string type;
	string name;
	float value;

	Node* root;
};

class SymbolTable {
private:
	vector<variable> variables;

public:
	int Lookup(string name) {
		for (variable variable : variables) {
			if (variable.name == name)
				return variable.value;
		}
		return 0;
	}

	bool Insert(string name, int value) {
		try {
			variable variable;
			variable.name = name;
			variable.value = value;

			variables.push_back(variable);
			return true;
		}
		catch (std::exception& e) {
			return false;
		}
	}
};

void addToTree(Node*& root, Node*& focusNode, string word, vector<variable>& variables) {

	// If word is an operator - place in parent node; move to said parent node
	if (isOperator(word)) {

		if (root == focusNode) {
			Node* newNode = new Node();
			newNode->value = word;
			newNode->child1 = root;

			root->parent = newNode;
			root = newNode;
			focusNode = newNode;
		}
		else {
			Node* newNode = new Node();
			newNode->value = word;

			Node* tempNode = focusNode;
			newNode->parent = focusNode->parent;
			focusNode->parent->child2 = newNode;
			newNode->child1 = tempNode;
			focusNode = newNode;
		}

	}
	else {
		string intValue = word;

		if (!isInteger(word)) {
			for (variable var : variables) {
				if (var.name == word) {
					intValue = std::to_string(var.value);

					if (intValue[0] == '-')
						intValue.erase(0, 1);

					break;
				}
			}
		}

		if (root == nullptr) {
			root = new Node();
			root->value = intValue;
			focusNode = root;
		}
		else {
			focusNode->value = intValue;
		}

	}
}

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
		else if ((std::find(std::begin(terminals), std::end(terminals), focus) != std::end(terminals)) || focus == "eof") {
			if (focus == getTermType(word)) {
				stack.pop_back();

				// If type declaring for a variable
				if (stack.back() == "VARTYPEAFTER") {
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

template<typename T>
T operate(T val1, T val2, string selfValue, vector<variable> variables) {
	if (selfValue == "+")
		return val1 + val2;
	if (selfValue == "-")
		return val1 - val2;
	if (selfValue == "*")
		return val1 * val2;
	if (selfValue == "/") {
		if (val2 == 0)
			throw std::invalid_argument("Divide by zero");

		return val1 / val2;
	}
	if (selfValue == "^") {
		int value = 1;
		for (int i = 0; i < val2; i++)
			value *= val1;
		return value;
	}

	string intValue = selfValue;

	if (!isInteger(selfValue)) {
		for (variable var : variables) {
			if (var.name == selfValue) {
				intValue = var.value;

				if (selfValue[0] == '-')
					intValue.erase(0, 1);

				break;
			}
		}
	}

	// if type is a float, return float string
	if (std::is_same<T, float>::value) {
		return std::stof(intValue);
	}

	// Otherwise return an int as a string
	return std::stoi(intValue);
}

template<typename T>
float nestNode(Node* curNode, string type, vector<variable> variables) {
	T val1 = 0;
	T val2 = 0;

	// Reverse order operation
	if (curNode->child1 != nullptr)
		val1 = nestNode<T>(curNode->child1, type, variables);
	if (curNode->child2 != nullptr)
		val2 = nestNode<T>(curNode->child2, type, variables);

	return operate<T>(val1, val2, curNode->value, variables);
}

float performCalc(Node* root, string type, vector<variable> variables) {

	if (root != nullptr)

		// Decide what type to pass in
		if (type == "ish")
			return nestNode<float>(root, type, variables);
		else
			return nestNode<int>(root, type, variables);

	else
		return 0;
}

int main()
{
	// Read in files 
	vector<string> file = readInFile("./ir.txt");

	// Create structures for the algorithm
	vector<vector<string>> productionTable = createProductionTable();
	map<string, map<string, int>> parseTable = createParseTable(productionTable);

	// Keep track of the IR
	vector < variable > variables;


	for (string line : file) {
		// Skip lines with comments
		if (line[0] == '/' && line[1] == '/') {
			std::cout << line << "\n";
			continue;
		}

		string passedStr = "invalid";
		string errorStr = "";

		// Keeps track of the values in a tree
		Node* root = nullptr;
		variable var;

		// Perform the algorithm
		if (checkLine(productionTable, parseTable, line, root, var, variables)) {
			try {
				passedStr = "valid";

				// Perform Math operation on line using post-order traversal and save into variables
				var.value = performCalc(root, var.type, variables);
				var.root = root;
				variables.push_back(var);
			}
			catch (std::exception e) {
				// passedStr = "invalid";
			}

		}

		std::cout << "(" << passedStr << "): " << line << "\n";
	}

	std::cout << "\n\nVariables\n";
	for (variable var : variables) {

		if (var.type == "num")
			std::cout << var.type << " " << var.name << " = " << (int)var.value << "\n";
		else
			std::cout << var.type << " " << var.name << " = " << var.value << "\n";


	}

	return 0;
}

