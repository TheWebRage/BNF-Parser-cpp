#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

// Terms and nonTerms - nonTerms are all caps(except for prime 'p'), terms are all lower
// Book Parts
// string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "TERM", "TERMp", "FACTOR" };
// string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num" };

//// Modified Parts
// string nonTerminals[] = { "GOAL", "EXPR", "EXPRp", "LTERM", "RTERM", "TERMp", "LFACTOR", "RFACTOR", "GFACTOR", "POSVAL", "SPACENEGVAL" };
// string terminals[] = { "eof", "+", "-", "*", "/", "(", ")", "name", "num", "negname", "negnum", "spacenegname", "spacenegnum" };

// IR Version
string nonTerminals[] = { "GOAL", "LINEFULL", "VARTYPEAFTER", "LINEVARNAME", "LINEVARNAMEREMAINING", "PROCEDUREPARAMS", "PARAMS", "MOREPARAMS", "VARTYPE", "EXPR", "LTERMADDSUB", "LTERMMULTDIV", "RTERMMULTDIV", "RTERMADDSUB", "ADDSUBp", "MULTDIVp", "MULTANDRIGHTOP", "DIVANDRIGHTOP", "POWERp", "POWERANDRIGHTOP", "LTERMPOWER", "RTERMPOWER", "GTERM", "PARENS", "POSVAL", "SPACENEGVAL" };
string terminals[] = { "eof", "+", "-", "*", "/", "=", "(", ")", "^", "num", "name", "negnum", "negname", "spacenegnum", "spacenegname", "{", "}", ",", "ish", "return", "procedure", "e", "readNum", "readIsh", "printNum", "printIsh" };
string operators[] = { "+", "-", "*", "/", "^" };
string ronts[] = { "RTERMADDSUB", "RTERMMULTDIV", "RTERMPOWER" };

vector<vector<string>> createProductionTable() {
	vector<vector<string>> productionTable;

	// Insert productions into structure

	// Book Table
	//productionTable.push_back({ "EXPR" });
	//productionTable.push_back({ "TERM", "EXPRp" });
	//productionTable.push_back({ "+", "TERM", "EXPRp" });
	//productionTable.push_back({ "-", "TERM", "EXPRp" });
	//productionTable.push_back({ "e" });
	//productionTable.push_back({ "FACTOR", "TERMp" });
	//productionTable.push_back({ "*", "FACTOR", "TERMp" });
	//productionTable.push_back({ "/", "FACTOR", "TERMp" });
	//productionTable.push_back({ "e" });
	//productionTable.push_back({ "(", "EXPR", ")" });
	//productionTable.push_back({ "num" });
	//productionTable.push_back({ "name" });


	//// Modified Version
	//productionTable.push_back({ "EXPR" });					// 0.   Goal ->Expr
	//productionTable.push_back({ "LTERM", "EXPRp" });		// 1.   Expr ->LTerm Expr’
	//productionTable.push_back({ "LFACTOR", "TERMp" });		// 2.   LTerm->LFactor Term’
	//productionTable.push_back({ "RFACTOR", "TERMp" });		// 3.   RTerm->RFactor Term’
	//productionTable.push_back({ "+", "RTERM", "EXPRp" });	// 4.   Expr’-> + RTerm Expr’
	//productionTable.push_back({ "-", "RTERM", "EXPRp" });	// 5.         | - RTerm Expr’
	//productionTable.push_back({ "e" });						// 6.         | e
	//productionTable.push_back({ "*", "RTERM", "TERMp" });	// 7.   Term’-> * RTerm Term’
	//productionTable.push_back({ "/", "RTERM", "TERMp" });	// 8.         | / RTerm Term’
	//productionTable.push_back({ "^", "RTERM", "TERMp" });	// 9 .        | ^ RTerm Expo`
	//productionTable.push_back({ "e" });						// 10.        | e
	//productionTable.push_back({ "GFACTOR" });				// 11. LFactor->GFactor
	//productionTable.push_back({ "negnum" });				// 12.        | negnum    //negative val without space only left term 
	//productionTable.push_back({ "negname" });				// 13.        | negname   //negative name without space only left term 
	//productionTable.push_back({ "GFACTOR" });				// 14. RFactor->GFactor
	//productionTable.push_back({ "(", "EXPR", ")" });		// 15. GFactor-> (Expr)
	//productionTable.push_back({ "POSVAL" });				// 16.        | PosVal
	//productionTable.push_back({ "SPACENEGVAL" });			// 17.        | SpaceNegVal
	//productionTable.push_back({ "num" });					// 18. PosVal->num
	//productionTable.push_back({ "name" });					// 19.        | name
	//productionTable.push_back({ "spacenegnum" });			// 20. SpaceNegVal->spacenegnum
	//productionTable.push_back({ "spacenegname" });			// 21.        | spacenegname

	// IR Version
	productionTable.push_back({ "LINEFULL" });
	productionTable.push_back({ "VARTYPE", "VARTYPEAFTER" });
	productionTable.push_back({ "LINEVARNAME" });
	productionTable.push_back({ "negnum", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "PARENS", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "return", "GTERM" });
	productionTable.push_back({ "}" });
	productionTable.push_back({ "LINEVARNAME" });
	productionTable.push_back({ "procedure", "name", "PROCEDUREPARAMS", "{" });
	productionTable.push_back({ "name", "LINEVARNAMEREMAINING" });
	productionTable.push_back({ "=", "EXPR" });
	productionTable.push_back({ "POWERANDRIGHTOP", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "MULTANDRIGHTOP", "ADDSUBp" });
	productionTable.push_back({ "DIVANDRIGHTOP", "ADDSUBp" });
	productionTable.push_back({ "ADDSUBp" });
	productionTable.push_back({ "(", "PARAMS", ")" });
	productionTable.push_back({ "VARTYPE", "name", "MOREPARAMS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ ",", "VARTYPE", "name", "MOREPARAMS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "num" });
	productionTable.push_back({ "ish" });
	productionTable.push_back({ "LTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "LTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "LTERMPOWER", "POWERp" });
	productionTable.push_back({ "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "RTERMPOWER", "POWERp" });
	productionTable.push_back({ "+", "RTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "-", "RTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "MULTANDRIGHTOP" });
	productionTable.push_back({ "DIVANDRIGHTOP" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "*", "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "/", "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "POWERANDRIGHTOP" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "^", "RTERMPOWER", "POWERp" });
	productionTable.push_back({ "GTERM" });
	productionTable.push_back({ "negnum" });
	productionTable.push_back({ "negname" });
	productionTable.push_back({ "GTERM" });
	productionTable.push_back({ "PARENS" });
	productionTable.push_back({ "POSVAL" });
	productionTable.push_back({ "SPACENEGVAL" });
	productionTable.push_back({ "(", "EXPR", ")" });
	productionTable.push_back({ "num" });
	productionTable.push_back({ "name" });
	productionTable.push_back({ "spacenegnum" });
	productionTable.push_back({ "spacenegname" });
	productionTable.push_back({ "readNum", "name" });
	productionTable.push_back({ "readIsh", "name" });
	productionTable.push_back({ "printNum", "name" });
	productionTable.push_back({ "printIsh", "name" });


	return productionTable;
}


string getTerm(int productionNum) {
	switch (productionNum) {
		//case 0:
		//	return "GOAL";
		//case 1:
		//	return "EXPR";
		//case 2:
		//	return "EXPRp";
		//case 3:
		//	return "EXPRp";
		//case 4:
		//	return "EXPRp";
		//case 5:
		//	return "TERM";
		//case 6:
		//	return "TERMp";
		//case 7:
		//	return "TERMp";
		//case 8:
		//	return "TERMp";
		//case 9:
		//	return "FACTOR";
		//case 10:
		//	return "FACTOR";
		//case 11:
		//	return "FACTOR";

	//case 0:
	//	return "GOAL";				// 0.   Goal ->Expr
	//case 1:
	//	return "EXPR";				// 1.   Expr ->LTerm Expr’
	//case 2:
	//	return "LTERM";				// 2.   LTerm->LFactor Term’			
	//case 3:
	//	return "RTERM";			// 3.   RTerm->RFactor Term’			
	//case 4:
	//	return "EXPRp";			// 4.   Expr’-> + RTerm Expr’			
	//case 5:
	//	return "EXPRp";			// 5.         | - RTerm Expr’			
	//case 6:
	//	return "EXPRp";			// 6.         | e			
	//case 7:
	//	return "TERMp";			// 7.   Term’-> * RTerm Term’	
	//case 8:
	//	return "TERMp";			// 8.         | / RTerm Term’
	//case 9:
	//	return "TERMp";			// 9.         | e
	//case 10:
	//	return "TERMp";
	//case 11:
	//	return "LFACTOR";			// 10. LFactor->GFactor
	//case 12:
	//	return "LFACTOR";			// 11.        | negnum    //negative val without space only left term 	
	//case 13:
	//	return "LFACTOR";			// 12.        | negname   //negative name without space only left term	
	//case 14:
	//	return "RFACTOR";			// 13. RFactor->GFactor	
	//case 15:
	//	return "GFACTOR";			// 14. GFactor-> (Expr)
	//case 16:
	//	return "GFACTOR";			// 15.        | PosVal
	//case 17:
	//	return "GFACTOR";			// 16.        | SpaceNegVal
	//case 18:
	//	return "POSVAL";			// 17. POSVAL -> | num
	//case 19:
	//	return "POSVAL";			// 18.           | name
	//case 20:
	//	return "SPACENEGVAL";		// 19. SpaceNegVal->spacenegnum
	//case 21:
	//	return "SPACENEGVAL";		// 20.        | spacenegname

	case 0:
		return"GOAL";
	case 1:
		return"LINEFULL";
	case 2:
		return"LINEFULL";
	case 3:
		return"LINEFULL";
	case 4:
		return"LINEFULL";
	case 5:
		return"LINEFULL";
	case 6:
		return"LINEFULL";
	case 7:
		return"VARTYPEAFTER";
	case 8:
		return"VARTYPEAFTER";
	case 9:
		return"LINEVARNAME";
	case 10:
		return"LINEVARNAMEREMAINING";
	case 11:
		return"LINEVARNAMEREMAINING";
	case 12:
		return"LINEVARNAMEREMAINING";
	case 13:
		return"LINEVARNAMEREMAINING";
	case 14:
		return"LINEVARNAMEREMAINING";
	case 15:
		return"PROCEDUREPARAMS";
	case 16:
		return"PARAMS";
	case 17:
		return"PARAMS";
	case 18:
		return"MOREPARAMS";
	case 19:
		return"MOREPARAMS";
	case 20:
		return"VARTYPE";
	case 21:
		return"VARTYPE";
	case 22:
		return"EXPR";
	case 23:
		return"LTERMADDSUB";
	case 24:
		return"LTERMMULTDIV";
	case 25:
		return"RTERMADDSUB";
	case 26:
		return"RTERMMULTDIV";
	case 27:
		return"ADDSUBp";
	case 28:
		return"ADDSUBp";
	case 29:
		return"ADDSUBp";
	case 30:
		return"MULTDIVp";
	case 31:
		return"MULTDIVp";
	case 32:
		return"MULTDIVp";
	case 33:
		return"MULTANDRIGHTOP";
	case 34:
		return"DIVANDRIGHTOP";
	case 35:
		return"POWERp";
	case 36:
		return"POWERp";
	case 37:
		return"POWERANDRIGHTOP";
	case 38:
		return"LTERMPOWER";
	case 39:
		return"LTERMPOWER";
	case 40:
		return"LTERMPOWER";
	case 41:
		return"RTERMPOWER";
	case 42:
		return"GTERM";
	case 43:
		return"GTERM";
	case 44:
		return"GTERM";
	case 45:
		return"PARENS";
	case 46:
		return"POSVAL";
	case 47:
		return"POSVAL";
	case 48:
		return"SPACENEGVAL";
	case 49:
		return"SPACENEGVAL";
	case 50:
		return"LINEFULL";
	case 51:
		return"LINEFULL";
	case 52:
		return"LINEFULL";
	case 53:
		return"LINEFULL";
	}

	return "";
}


/* New Table
* 

// Terms and nonTerms - nonTerms are all caps(except for prime 'p'), terms are all lower
string nonTerminals[] = { "GOAL", "LINEFULL", "VARTYPEAFTER", "LINEVARNAME", "LINEVARNAMEREMAINING", "PROCEDUREPARAMS", "PARAMS", "MOREPARAMS", "VARTYPE", "EXPR", "LTERMADDSUB", "LTERMMULTDIV", "RTERMMULTDIV", "RTERMADDSUB", "ADDSUBp", "MULTDIVp", "MULTANDRIGHTOP", "DIVANDRIGHTOP", "POWERp", "POWERANDRIGHTOP", "LTERMPOWER", "RTERMPOWER", "GTERM", "PARENS", "POSVAL", "SPACENEGVAL" };
string terminals[] = { "eof", "+", "-", "*", "/", "=", "(", ")", "^", "num", "name", "negnum", "negname", "spacenegnum", "spacenegname", "{", "}", ",", "ish", "return", "procedure", "e" };
string operators[] = { "+", "-", "*", "/", "^" };
string ronts[] = { "RTERMADDSUB", "RTERMMULTDIV", "RTERMPOWER" };

vector<vector<string>> createProductionTable() {
	vector<vector<string>> productionTable;

	productionTable.push_back({ "LINEFULL" });
	productionTable.push_back({ "VARTYPE", "VARTYPEAFTER" });
	productionTable.push_back({ "LINEVARNAME" });
	productionTable.push_back({ "EXPRWITHOUTNAME" });
	productionTable.push_back({ "return", "GTERM" });
	productionTable.push_back({ "return", "GTERM" });
	productionTable.push_back({ "if", "(", "CONDITION", ")", "{" });
	productionTable.push_back({ "else", "{" });
	productionTable.push_back({ "}" });
	productionTable.push_back({ "printNum", "name" });
	productionTable.push_back({ "printIsh", "name" });
	productionTable.push_back({ "readNum", "name" });
	productionTable.push_back({ "readIsh", "name" });
	productionTable.push_back({ "printString" }); 
	productionTable.push_back({ "LINEVARNAME" });
	productionTable.push_back({ "procedure", "name", "PROCEDUREPARAMS", "{" });
	productionTable.push_back({ "name", "LINEVARNAMEREMAINING" });
	productionTable.push_back({ "=", "EXPR" });
	productionTable.push_back({ "POWERANDRIGHTOP", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "MULTANDRIGHTOP", "ADDSUBp" });
	productionTable.push_back({ "DIVANDRIGHTOP", "ADDSUBp" });
	productionTable.push_back({ "ADDSUBp" });
	productionTable.push_back({ "num_value", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "negnum_value", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "PARENS", "POWERp", "MULTDIVp", "ADDSUBp" });
	productionTable.push_back({ "EXPR", "=", "EXPR" });
	productionTable.push_back({ "EXPR", "!=", "EXPR" });
	productionTable.push_back({ "(", "PARAMS", ")" });
	productionTable.push_back({ "VARTYPE", "name", "MOREPARAMS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ ",", "VARTYPE", "name", "MOREPARAMS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "num" });
	productionTable.push_back({ "ish" });
	productionTable.push_back({ "LTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "LTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "LTERMPOWER", "POWERp" });
	productionTable.push_back({ "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "RTERMPOWER", "POWERp" });
	productionTable.push_back({ "+", "RTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "-", "RTERMADDSUB", "ADDSUBp" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "MULTANDRIGHTOP" });
	productionTable.push_back({ "DIVANDRIGHTOP" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "*", "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "/", "RTERMMULTDIV", "MULTDIVp" });
	productionTable.push_back({ "POWERANDRIGHTOP" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "^", "RTERMPOWER", "POWERp" });
	productionTable.push_back({ "GTERM" });
	productionTable.push_back({ "negnum_value" });
	productionTable.push_back({ "negish_value" });
	productionTable.push_back({ "negname" });
	productionTable.push_back({ "GTERM" });
	productionTable.push_back({ "NAMEORPROCEDURE" });
	productionTable.push_back({ "PARENS" });
	productionTable.push_back({ "num_value" });
	productionTable.push_back({ "ish_value" });
	productionTable.push_back({ "SPACENEGVAL" });
	productionTable.push_back({ "name", "ARGUMENTS" });
	productionTable.push_back({ "(", "EXPR", "MOREARGUMENTS", ")" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ ",", "EXPR", "MOREARGUMENTS" });
	productionTable.push_back({ "e" });
	productionTable.push_back({ "(", "EXPR", ")" });
	productionTable.push_back({ "spacenegnum_value" });
	productionTable.push_back({ "spacenegish_value" });
	productionTable.push_back({ "spacenegname" });


	return productionTable;
}


string getTerm(int productionNum) {
	switch (productionNum) {
	case 0:
		return"GOAL";
	case 1:
		return"LINEFULL";
	case 2:
		return"LINEFULL";
	case 3:
		return"LINEFULL";
	case 4:
		return"LINEFULL";
	case 5:
		return"LINEFULL";
	case 6:
		return"LINEFULL";
	case 7:
		return"LINEFULL";
	case 8:
		return"LINEFULL";
	case 9:
		return"LINEFULL";
	case 10:
		return"LINEFULL";
	case 11:
		return"LINEFULL";
	case 12:
		return"LINEFULL";
	case 13:
		return"VARTYPEAFTER";
	case 14:
		return"VARTYPEAFTER";
	case 15:
		return"LINEVARNAME";
	case 16:
		return"LINEVARNAMEREMAINING";
	case 17:
		return"LINEVARNAMEREMAINING";
	case 18:
		return"LINEVARNAMEREMAINING";
	case 19:
		return"LINEVARNAMEREMAINING";
	case 20:
		return"LINEVARNAMEREMAINING";
	case 21:
		return"EXPRWITHOUTNAME";
	case 22:
		return"EXPRWITHOUTNAME";
	case 23:
		return"EXPRWITHOUTNAME";
	case 24:
		return"CONDITION";
	case 25:
		return"CONDITION";
	case 26:
		return"PROCEDUREPARAMS";
	case 27:
		return"PARAMS";
	case 28:
		return"PARAMS";
	case 29:
		return"MOREPARAMS";
	case 30:
		return"MOREPARAMS";
	case 31:
		return"VARTYPE";
	case 32:
		return"VARTYPE";
	case 33:
		return"EXPR";
	case 34:
		return"LTERMADDSUB";
	case 35:
		return"LTERMMULTDIV";
	case 36:
		return"RTERMADDSUB";
	case 37:
		return"RTERMMULTDIV";
	case 38:
		return"ADDSUBp";
	case 39:
		return"ADDSUBp";
	case 40:
		return"ADDSUBp";
	case 41:
		return"MULTDIVp";
	case 42:
		return"MULTDIVp";
	case 43:
		return"MULTDIVp";
	case 44:
		return"MULTANDRIGHTOP";
	case 45:
		return"DIVANDRIGHTOP";
	case 46:
		return"POWERp";
	case 47:
		return"POWERp";
	case 48:
		return"POWERANDRIGHTOP";
	case 49:
		return"LTERMPOWER";
	case 50:
		return"LTERMPOWER";
	case 51:
		return"LTERMPOWER";
	case 52:
		return"LTERMPOWER";
	case 53:
		return"RTERMPOWER";
	case 54:
		return"GTERM";
	case 55:
		return"GTERM";
	case 56:
		return"GTERM";
	case 57:
		return"GTERM";
	case 58:
		return"GTERM";
	case 59:
		return"NAMEORPROCEDURE";
	case 60:
		return"ARGUMENTS";
	case 61:
		return"ARGUMENTS";
	case 62:
		return"MOREARGUMENTS";
	case 63:
		return"MOREARGUMENTS";
	case 64:
		return"PARENS";
	case 65:
		return"POSVAL";
	case 66:
		return"POSVAL";
	case 67:
		return"SPACENEGVAL";
	case 68:
		return"SPACENEGVAL";
	case 69:
		return"SPACENEGVAL";
	}

	return "";
}

* 
* 
* 
*/