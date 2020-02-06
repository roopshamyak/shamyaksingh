#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "token.h"

//---------------------------------------------------------------------------------------
//                                gets/sets
//---------------------------------------------------------------------------------------
symTblRef token::getRef() { return ref; }
TOKENID   token::getId() { return id; }
void      token::setId(TOKENID tid) { id = tid; }
void      token::setRef(symTblRef tref) { ref = tref; }

//---------------------------------------------------------------------------------------
//                                getPrintString
//---------------------------------------------------------------------------------------
string    token::getPrintString() {
	stringstream m;
	m << "TOK:  ID=" << right << setw(2) << to_string((int)id) << " " << left << setw(15)
	  << TOKENID_STR[(int)id];
	if (ref) m << "LEX=" << (ref->getLex()) << endl;
	else if ((int)id <= LAST_TOK_RESWD_NDX) m << "RESWD" << endl;
	else m << "NON-TERM" << endl;
	return m.str();
} //getPrintString()