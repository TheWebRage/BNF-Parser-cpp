#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>

#include "constants.cpp"

using std::string;
using std::vector;
using std::set;
using std::map;
using std::ifstream;


vector<string> readInFile(string filePath) {
	vector<string> lines;
	ifstream file;
	file.open(filePath, std::ios::out);
	if (!file) {
		// File coun't open
		cout << "Couldn't file file " << filePath;
	}
	else {
		string line;
		while (getline(file, line))
			lines.push_back(line);

		file.close();
	}
	return lines;
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

int getNonTermStart(string term, vector<vector<string>> productionTable) {
	for (int i = 0; i < productionTable.size(); i++) {
		if (getTerm(i) == term)
			return i;
	}
	return 0;
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

string removeBeginSpace(string eraseString) {
	while (eraseString[0] == ' ') {
		eraseString.erase(0, 1);
	}
	return eraseString;
}

bool isInString(string compString, char compChar) {
	for (char ch : compString)
		if (ch == compChar)
			return true;

	return false;
}