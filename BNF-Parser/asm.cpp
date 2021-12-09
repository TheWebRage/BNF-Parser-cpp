#pragma once

#include <string>

using std::string;

string startFile() {
    return
        "section.data"
        "msg : db \"Hello, this is my string\", 0"
        "fmtstr : db \"%s\", 10, 0"
        "fmtuint : db \"%d\", 10, 0"
        "fmtuintin : db \"%d\", 0"
        "fmtfloatin : db \"%f\", 0"
        "float1 : dd     0.0"
        ""
        "section.bss"
        "var1 : resd   1"
        ""
        "section.text"
        ""
        "extern printf"
        "extern scanf"
        "global main"
        "main :"
        "push rbp; Push base pointer onto stack to save it";
;
}

string printString(string outfile, string strName) {
    return outfile + ""
        ""
        "; print a string"
        "mov rsi, " + strName + ""
        "mov rdi, fmtstr"
        "mov rax, 0"
        "call printf";
}

string printNum(string outfile, string varName) {
    return outfile + ""
        ""
        "; print integer back out"
        "lea rdi, [fmtuint]"
        "mov rsi, [" + varName + "]"
        "xor rax, rax"
        "call printf";
}

string readNum(string outfile, string varName) {
    return outfile + ""
        ""
        "; read an integer"
        "lea rdi, [fmtuintin]"
        "lea rsi, [" + varName + "]"
        "mov rax, 0"
        "call scanf";
}

