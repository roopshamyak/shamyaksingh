#include "symbol.h"

//-----------------------------------------------------
//						constructor
//-----------------------------------------------------
symbol::symbol() {
	lexeme = "";
	category = dataType = 0;
	next = NULL;
}

//-----------------------------------------------------
//					simple gets/sets
//-----------------------------------------------------
void   symbol::setDataType(int dt) { dataType = dt; }
string symbol::getLex() { return lexeme; }
int    symbol::getCategory() { return category; }
int    symbol::getDataType() { return dataType; }

//-----------------------------------------------------
//					    setLex
//-----------------------------------------------------
void   symbol::setLex(string lex) {
	lexeme = lex;

	//TO DO: set category and data type.
	// myvar,		'Hello',	 12.5,      12
	// identifier,	string lit,	 real lit,  int lit
	if (lex[0] == '\'') {
		category = SYMCAT_STRING_LIT;
		dataType = DTYPE_STRING;
	}
	else if (lex[0] >= '0' && lex[0] <= '9') {
		category = SYMCAT_INT_LIT;
		dataType = DTYPE_INT;
		for (int i=0; i<(int)lex.length(); i++)
			if (lex[i] == '.') {
				category = SYMCAT_REAL_LIT;
				dataType = DTYPE_REAL;
			}

	}
	else {
		category = SYMCAT_IDENT;
		dataType = DTYPE_UNKNOWN;
	}
} // setLex()
