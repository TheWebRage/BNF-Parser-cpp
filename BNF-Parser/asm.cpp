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

string printString(string outfile, string strName) {
    return outfile + "\n"
        "\n"
        "; print a string\n"
        "mov rsi, " + strName + "\n"
        "mov rdi, fmtstr\n"
        "mov rax, 0\n"
        "call printf\n";
}

string printNum(string outfile, string varName) {
    return outfile + "\n"
        "\n"
        "; print integer back out\n"
        "lea rdi, [fmtuint]\n"
        "mov rsi, [" + varName + "]\n"
        "xor rax, rax\n"
        "call printf\n";
}

string readNum(string outfile, string varName) {
    return outfile + "\n"
        "\n"
        "; read an integer\n"
        "lea rdi, [fmtuintin]\n"
        "lea rsi, [" + varName + "]\n"
        "mov rax, 0\n"
        "call scanf\n";
}


// TODO: NOTES: 
// - procedures are just labels with scope
// - before a procedure label is made, make a jump to the end of the procedure
// - any { creates new scope on stack
// - any } ends current scope and returns the old stack
// - print calls are done before check line is called and just done by hand


// TODO: BUGS:
// - Some vars are created with empty names
// - 

