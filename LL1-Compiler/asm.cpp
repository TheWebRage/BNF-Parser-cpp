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
        "\n"
        "section.bss\n"
        "result: resd 1\n";

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
        "main:\n"
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

string callFunction(string label) {
    return "\ncall " + label;
}

string movValInReg(string val, string reg = "ebx") {
    return "\nmov " + reg + ", " + val;
}

string movVarInReg(string varName, string reg = "ebx") {
    return "\nmov " + reg + ", [" + varName + "]";
}

string movRegInVar(string varName, string reg = "ebx") {
    return "\nmov [" + varName + "], eax\n"; // This will always need to return eax into memory
}

// TODO: create a class to operation overload to output to asm with template types
string operationEq(variable var) {
    int value = var.value;

    string output = "\nmov eax, " + std::to_string(value);
    output += "\nmov [" + var.name + "], eax\n";

    return output;
}

string operationPlus() {
    return "\nadd eax, ebx";
}

string operationMinus() {
    return "\nsub eax, ebx";
}

string operationMult() {
    return "\nimul eax, ebx";
}

string operationDiv() {
    return "\ndiv ebx";
}

char nextPowerNum = 'a';

string operationPow() {
    nextPowerNum++;
    string nextNum = std::to_string(nextPowerNum);
    string output = "\n\nxor edi, edi\nmov r8, 1\nmov r9, eax\nexp_start" + nextNum + ":\ncmp edi, ebx\njz exp_done" + nextNum;
    output += "\nimul r8, ecx\ninc edi\njmp exp_start" + nextNum;
    output += "\nexp_done" + nextNum;
    output += ":\n";
    return output;
}

string asmSyscall() {

}

string getOperationString(Node* curNode, string& output, bool& isFirstVar, vector<string> labels) {
    // Post-order traversal
    if (curNode->child1 != nullptr)
        getOperationString(curNode->child1, output, isFirstVar, labels);
    if (curNode->child2 != nullptr)
        getOperationString(curNode->child2, output, isFirstVar, labels);

    // If value in curNode = variable or value
    // - Add "mov eax, <value>" to output then return
    if (!isOperator(curNode->value)) {

        // Distinguish between eax and ebx
        string regName = "ebx";

        if (isFirstVar) regName = "eax";
        
        // Int value
        if (std::isdigit((curNode->value)[0])) {
            output += movVarInReg(curNode->value, regName);
        }

        // Assume Variable
        else {
            for (string label : labels) {
                if (label == curNode->value) {
                    return ""; // TODO: make function call procedureal
                }
            }

            output += movValInReg(curNode->value, regName);
        }

        isFirstVar = false;
        return "";
    }
    
    // If value in curNode = operator
    else {
        // Add operation method to output then return
        if (curNode->value == "+") {
            output += operationPlus();
        }
        else if (curNode->value == "-") {
            output += operationMinus();
        }
        else if (curNode->value == "*") {
            output += operationMult();
        }
        else if (curNode->value == "/") {
            output += operationDiv();
        }
        else if (curNode->value == "^") {
            output += operationPow();
        }
    }

    return "";
}

// Starts the getOperationString process
void getOpString(Node* root, string& output, string varName, vector<string> labels) {
    bool isFirstVar = true;
    getOperationString(root, output, isFirstVar, labels);
    output += movRegInVar(varName);
}

string asmPushStack() {
    return "\npush rax\npush rbx\n";
}

string asmPopStack() {
    return "\npop rbx\npop rax\n";
}

string asmSetProcedureLabel(string procedureName) {
    return "\n\njmp " + procedureName + "end\n" + procedureName + ":\n";
}

string asmReturn(string procedureName, string varName) {
    return asmPopStack() + "\nmov eax, [" + varName + "]\nret \n" + procedureName + "end: \n\n";
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
// - floats printing (as ints) - Don't print in asm at all?

