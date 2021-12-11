#pragma once

#include <string>
#include <vector>

#include "IR.cpp"

using std::string;
using std::vector;


string startFile(vector<variable> variables) {
    string output = "\n"
        "section.data\n"
        "msg : db \"Hello, this is my string\", 0\n"
        "fmtstr : db \"%s\", 10, 0\n"
        "fmtuint : db \"%d\", 10, 0\n"
        "fmtuintin : db \"%d\", 0\n"
        "fmtfloatin : db \"%f\", 0\n"
        "float1 : dd     0.0\n"
        "\n"
        "section.bss\n";

    for (variable var : variables) {
        output += "\n" + var.name + ": resd 1";
    }
        
        
    output += "\n"
        "\n"
        "section.text\n"
        "\n"
        "extern printf\n"
        "extern scanf\n"
        "global main\n"
        "main :\n"
        "push rbp; Push base pointer onto stack to save it\n";

    return output;
}

string printString(string strName) {
    return "\n"
        "\n"
        "; print a string\n"
        "mov rsi, " + strName + "\n" // TODO: Check this asm works correctly
        "mov rdi, fmtstr\n"
        "mov rax, 0\n"
        "call printf\n";
}

string printNumVar(string varName) {
    return "\n"
        "\n"
        "; print integer back out\n"
        "lea rdi, [fmtuint]\n"
        "mov rsi, [" + varName + "]\n"
        "xor rax, rax\n"
        "call printf\n";
}

string readNum(string varName) {
    return "\n"
        "\n"
        "; read an integer\n"
        "lea rdi, [fmtuintin]\n"
        "lea rsi, [" + varName + "]\n"
        "mov rax, 0\n"
        "call scanf\n";
}

// TODO: create a class to operation overload to output to asm with template types
string operationEq(variable var) {
    string output = "\nmov eax, " + (int)var.value;
    output += "\nmov [" + var.name + "], eax\n";

    return output;
}

string operationPlus(variable var1, variable var2) {
    string output = "\nmov eax, " + (int)var1.value;
    output += "\naddi eax, " + (int)var2.value;
    output += "\nmov [" + var1.name + "], eax\n";

    return output;
}

string operationMinus(variable var1, variable var2) {
    string output = "\nmov eax, " + (int)var1.value;
    output += "\naddi eax, " + (int)var2.value;
    output += "\nmov [" + var1.name + "], eax\n";

    return output;
}

string operationMult(variable var1, variable var2) {
    string output = "\nmov eax, " + (int)var1.value;
    output += "\nmuli eax, " + (int)var2.value;
    output += "\nmov [" + var1.name + "], eax\n";

    return output;
}

string operationDiv(variable var1, variable var2) {
    string output = "\nmov eax, " + (int)var1.value;
    output += "\ndivi eax, " + (int)var2.value;
    output += "\nmov [" + var1.name + "], eax\n";

    return output;
}

string operationPow(variable var1, variable var2) {
    string output = "\nmov eax, " + (int)var1.value;
    output += "\naddi eax, " + (int)var2.value; // TODO: get all operations working correctly
    output += "\nmov [" + var1.name + "], eax\n";

    return output;
}

string getOperationString(Node* curNode, string* output) {
    int var1, var2;
    
    // TODO: make system for both vars and values
    if (curNode->child1 != nullptr)
        var1 = getOperationString(curNode->child1, output);
    if (curNode->child2 != nullptr)
        vargetOperationString(curNode->child2, output);

    // If value in curNode = variable or value
    if (!isOperator(curNode->value)) {
        // Add "mov eax, <value>" to output then return
    }
    
    // If value in curNode = operator
    else {
        // Add operation method to output then return
        if (curNode->value == "+") {
            output += operationPlus(); // TODO: finish this
        }
        else if (curNode->value == "-") {

        }
        else if (curNode->value == "*") {

        }
        else if (curNode->value == "/") {

        }
        else if (curNode->value == "^") {

        }
    }
}

string getPrintString(string line, vector<variable> variables) {
    if (line.find("printNum ") != string::npos) {
        line.erase(0, 9);
        removeBeginSpace(line);

        // Find var to print
        for (variable var : variables) {
            if (var.name == line)
                return printNumVar(line);
        }
    }

    if (line.find("printString ") != string::npos) {
        line.erase(0, 11);
        removeBeginSpace(line);
        return printString(line);
    }

    return "";
}

// TODO: NOTES: 
// - procedures are just labels with scope
// - before a procedure label is made, make a jump to the end of the procedure
// - any { creates new scope on stack
// - any } ends current scope and returns the old stack
// - print calls are done before check line is called and just done by hand


// TODO: BUGS:
// - Some vars are created with empty names
// - asm print string are getting too many lines

