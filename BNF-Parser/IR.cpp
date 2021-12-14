#pragma once

#include <string>
#include <vector>

#include "helpers.cpp"

using std::string;
using std::vector;


class Node {
public:

	string value = "";

	Node* child1;
	Node* child2;

	Node* parent;
};

class variable {
public:

	string type;
	string name;
	float value;

	bool isOptimized = false;

	Node* root;
};

variable* findVariableByName(vector<variable> variables, string name) {
	for (variable var : variables) {
		if (var.name == name)
			return &var;
	}

	return nullptr;
}

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
				if (var.name == word && var.isOptimized) {
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

		// Var not found in list

	}

	// if type is a float, return float string
	if (std::is_same<T, float>::value) {
		return std::stof(intValue);
	}

	// Otherwise return an int as a string
	return std::stoi(intValue);
}

bool shouldWaitForRuntime(Node* curNodeChild) {
	return curNodeChild != nullptr && (!std::isdigit(curNodeChild->value[0]) && !isOperator(curNodeChild->value));
}

template<typename T>
float nestNode(Node* curNode, string type, vector<variable> variables) {
	T val1;
	T val2;

	// if one of the children is a name, it needs to wait for runtime
	if (shouldWaitForRuntime(curNode->child1) || shouldWaitForRuntime(curNode->child2)) {
		throw std::runtime_error("This needs to be executed at runtime");
	}

	// Reverse order operation
	if (curNode->child1 != nullptr)
		val1 = nestNode<T>(curNode->child1, type, variables);
	if (curNode->child2 != nullptr)
		val2 = nestNode<T>(curNode->child2, type, variables);

	T value = operate<T>(val1, val2, curNode->value, variables);
	return value;
}

float performCalc(Node* root, string type, vector<variable> variables) {

	if (root != nullptr)
		// TODO: Check to see if the operation has to wait for runtime

		// Decide what type to pass in
		if (type == "ish")
			return nestNode<float>(root, type, variables);
		else
			return nestNode<int>(root, type, variables);

	else
		return 0;
}
