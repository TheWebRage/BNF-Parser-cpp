#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <regex>

#include "constants.cpp""
#include "helpers.cpp"

using std::string;
using std::vector;
using std::set;
using std::map;
using std::regex;


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
	if (!(isTerminal(word))) {

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