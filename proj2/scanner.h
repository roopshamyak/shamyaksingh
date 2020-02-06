#pragma once
#include <fstream>
#include <string>
#include "fsa.h"
#include "token.h"
#include "symTbl.h"

using namespace std;

class scanner {
public:
	int	   open(string source);
	string getError() { return error; }
	bool   isError() { return is_error; }
	token  getNextToken();
	void   close();
private:
	string error = "";
	bool   is_error = false;
	int    lineNo = 1;
	ifstream f;

	CHAR_CAT categorize(char c);
	void    setError(string method, char c, string msg);
	int     getTrans(FSA_STATE currState, char c);
	string  getFSAerror(CHAR_CAT cc, FSA_STATE state);
	string  getNextLexeme();
	TOKENID resWordToTokenId(string lex);
	symTbl  symbolTbl;
	string  upcase(string s);
	TOKENID symCatToTokId(int cat);
};





