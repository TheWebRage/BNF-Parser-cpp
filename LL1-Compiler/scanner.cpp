#pragma once

#include <string>

#include "helpers.cpp"

using std::string;


// NOTE: This is just a hand made scanner. There was not enough time in class to have a scanner algorithm homework.

string nextWord(string line, bool isNegVal = false) {
	char keyTerms[] = { '+', '-', '*', '/', '(', ')', '^', ',' };
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
