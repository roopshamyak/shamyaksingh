//  +-------------------------------------------+
//  |                 parser.h                  |
//  +-------------------------------------------+

#pragma once
#include <string>
#include <stack>
#include "scanner.h"
using namespace std;

class parser {
public:
	string compile(string fn);
private:
	stack <token> tokStack;
	scanner scan;

	token top, nextToken;
	string parseError = "";

	int selectProd();
	bool isNonTerminal(token t);
	void pushProdRHS(int prodNum);
	bool startup(string filename);

};