#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

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

string getTerm(int productionNum) {
	switch (productionNum) {
	case 0:
		return "GOAL";
	case 1:
		return "EXPR";
	case 2:
		return "EXPRp";
	case 3:
		return "EXPRp";
	case 4:
		return "EXPRp";
	case 5:
		return "TERM";
	case 6:
		return "TERMp";
	case 7:
		return "TERMp";
	case 8:
		return "TERMp";
	case 9:
		return "FACTOR";
	case 10:
		return "FACTOR";
	case 11:
		return "FACTOR";
	}

	return "";
}

bool isProduction(string nonTerm, int productionNum) {
	return ((nonTerm == "GOAL" && productionNum == 0)
		|| (nonTerm == "EXPR" && productionNum == 1)
		|| (nonTerm == "EXPRp" && productionNum == 2)
		|| (nonTerm == "EXPRp" && productionNum == 3)
		|| (nonTerm == "EXPRp" && productionNum == 4)
		|| (nonTerm == "TERM" && productionNum == 5)
		|| (nonTerm == "TERMp" && productionNum == 6)
		|| (nonTerm == "TERMp" && productionNum == 7)
		|| (nonTerm == "TERMp" && productionNum == 8)
		|| (nonTerm == "FACTOR" && productionNum == 9)
		|| (nonTerm == "FACTOR" && productionNum == 10)
		|| (nonTerm == "FACTOR" && productionNum == 11));
}

bool isNonTerminal(string term) {
	for (int i = 0; i < nonTerminals.size(); i++) {
		if (term == nonTerminals[i])
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
    for(auto it = set1.begin(); it != set1.end(); ++it) {
        if (*it == removeStr) {
            set1.erase(it);
            return set1;
        }
    }
    return set1;
}

void first(vector< vector<string> > productionTable, map< string, set<string> >& firstTable) {

	map<string, set<string>> firstTableCopy = firstTable;
	bool changing = true;

	while (changing) {
		for (int j = 0; j < productionTable.size(); j++) {
			vector<string> production = productionTable[j];
			set<string> rhs = removeElement(firstTable[production[0]], "e");
			int i = 1;

			for (int c = 0; c < production.size(); c++) {
				string part = production[c];
				if (part == "e" && i+1 <= production.size() - 1) {
					rhs = unionSets(rhs, firstTable[production[i+1]]); // TODO: fix this
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
		} else {
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
	while(changing) {
		for (int j = 0; j < productionTable.size(); j++) {
			vector<string> production = productionTable[j];

			set<string> trailer = followTable[getTerm(j)];
			int k = production.size();

			for (int i = k - 1; i >= 0; --i) {
				if (isNonTerminal(production[i])) {
					followTable[production[i]] = unionSets(followTable[production[i]], trailer);

					if (firstTable[production[i]].find("e") != firstTable[production[i]].end()) {
						trailer = unionSets(trailer, removeElement(firstTable[production[i]], "e"));
					} else {
						trailer = firstTable[production[i]];
					}

				} else {
					trailer = firstTable[production[i]];
				}

			}
		}

		if (followTableCopy == followTable) {
			changing = false;
		} else {
			followTableCopy = followTable;
		}
	}

//	while (FOLLOW sets are still changing) do;
//		for each p ∈ P of the form A→β1β2 ···βk do;
//		TRAILER ← FOLLOW(A);
//		for i ← k down to 1 do;
//			if βi ∈ N T then begin;
//				FOLLOW(βi) ← FOLLOW(βi) ∪ TRAILER;
//					if  ∈ FIRST(βi)
//						then TRAILER ← TRAILER ∪(FIRST(βi) − );
//					else TRAILER ← FIRST(βi);
//					end;
//			else TRAILER ← FIRST(βi); // is {βi}
//			end;
//		end;
//end;

}

map<string, vector<string>> firstPlus(vector<vector<string>> productionTable, int production, map<string, vector<string>> firstTable, map<string, vector<string>> followTable) {
	// // if e in first() then first()
	// //if (std::find(std::begin(firstTable), std::end(firstTable), "e") != std::end(firstTable))
	// //	return firstTable;
	// // else first() and follow()
	//if (std::find(std::begin(firstTable), std::end(firstTable), "e") == std::end(firstTable)) {
	//	for (string part : followTable[production])
	//		firstTable[productionTable[production][0]].push_back(part);
	//}

    return firstTable;
}

map<string, map<string, int>> createParseTable(vector< vector<string> > productionTable) {

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
	map< string, set<string> > firstTable;
	for (string term : terminals) {
		firstTable[term].insert(term);
	}
	for (string nonTerm : nonTerminals) {
		firstTable[nonTerm].clear();
	}

	first(productionTable, firstTable);


	map< string, set<string> > followTable;
	follow(productionTable, followTable, firstTable);

	//map<string, vector<string>> firstPlusTable = firstPlus(productionTable, 0, firstTable, followTable);
	//int parse_table[non_terms.size()][terms.size()];
	
	for (int i = 0; i < productionTable.size(); i++) {
		vector<string> rhs = productionTable[i];

		set<string> nextList;
		bool finished = false;
		for (auto ch = rhs.begin(); ch != rhs.end(); ++ch) {
			// If first part in production a non term, add it to firsts list
			if (isNonTerminal(*ch)) {
				if (*ch != "e") {
					nextList.insert(*ch);
					finished = true;
					break;
				}
				continue;
			}

			set<string> firstTableCopy(firstTable[*ch].begin(), firstTable[*ch].end());
			if (firstTableCopy.find("e") == firstTableCopy.end()) {
				nextList.insert(firstTableCopy.begin(), firstTableCopy.end());
				finished = true;
				break;
			}
			firstTableCopy.erase("e");
			nextList.insert(firstTableCopy.begin(), firstTableCopy.end());
		}
		// If the whole rhs can be skipped through epsilon or reaching the end
		// Add follow to next list
		if (!finished) {
			nextList.insert(followTable[getTerm(i)].begin(), followTable[getTerm(i)].end());
		}


		for (auto ch = nextList.begin(); ch != nextList.end(); ++ch) {
			parseTable[getTerm(i)][productionTable[i][0]] = i;
		}

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

