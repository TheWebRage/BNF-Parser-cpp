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

void first(vector<vector<string>> productionTable) {
	map<string, string> firstTable;

	for (string term : terminals)
		firstTable[term] = term;

	for (string nonTerm : nonTerminals)
		firstTable[nonTerm] = "";

	bool hasChanged = true;
	while (hasChanged) {
		for (vector<string> production : productionTable) {
			// TODO: Maybe if statement here?
			string rhs = firstTable[production[0]];
			int i = 1;
			for (i; i <= production.size() && firstTable[production[i]] == "e"; i++) {
				for (int j = 0; j < firstTable[production[i]].size(); j++) {
					if (firstTable[production[i + 1]] != "e")
						rhs += firstTable[production[i + 1]]; // TODO: is this right?
				}
			}

			bool foundE = false;

			for (int j = 0; j < firstTable[production.back()]; j++) {

			}

			if (i == production.size() && ) {

			}
		}

	}
}

void follow() {
//	for each A ∈ N T do;
//	FOLLOW(A) ← ∅;
//	end;
//	FOLLOW(S) ← { eof };
//	while (FOLLOW sets are still changing) do;
//	for each p ∈ P of the form A→β1β2 ···βk do;
//	TRAILER ← FOLLOW(A);
//	for i ← k down to 1 do;
//	if βi ∈ N T then begin;
//	FOLLOW(βi
//	) ← FOLLOW(βi
//	) ∪ TRAILER;
//	if  ∈ FIRST(βi
//	)
//		then TRAILER ← TRAILER ∪(FIRST(βi
//		) − );
//	else TRAILER ← FIRST(βi
//	);
//	end;
//	else TRAILER ← FIRST(βi
//	); // is {βi
//}
//end;
//end;
//end;
}

void firstPlus() {
	// if e in first() then first()
	// else first() and follow()
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
	//for each nonterminal A do;
	//for each terminal w do;
	//Table[A, w] <- error;
	//end;
	//for each production p of the form A->B do;
	//for each terminal w in FIRST + (A->B) do;
	//Table[A, w] < -p;
	//end;
	//if eof in FIRST + (A→B)
	//	then Table[A, eof] < -p;
	//end;
	//end;

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
	map<string, map<string, int>> parseTable = createParseTable();

	for (string line : file) {
		string passedStr = "invalid";

		// Perform the algorithm
		if (checkLine(productionTable, parseTable, line))
			passedStr = "valid";

		std::cout << "(" << passedStr << "): " << line << "\n";
	}

	return 0;
}

