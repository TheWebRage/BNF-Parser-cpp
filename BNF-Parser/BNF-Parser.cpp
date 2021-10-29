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

string getFocus(string word) {
	if (!(std::find(std::begin(terminals), std::end(terminals), word) != std::end(terminals))) {
		if (std::isdigit(word[0]))
			return "num";
		else
			return "name";
	}

	return word;
}

string nextWord(string& line) {
	char keyTerms[] = { '+', '-', '*', '/', '(', ')' };
	string word = "";

	if (line.size() > 0) {
		word += line[0];

		for (int i = 0; i < line.length(); i++) {
			for (char term : keyTerms) {
				if (line[i] == term || line[i] == ' ') {
					break;
				}
			}

			word += line[i];
		}
	}

	line.erase(0, word.size());

	if (word == "")
		word = "eof";

	return getFocus(word);
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
			if (focus == word) {
				stack.pop_back();
				word = nextWord(line);
			}
			else {
				// else report an error looking for symbol at top of stack;
				return 0;
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

