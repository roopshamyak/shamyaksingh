#include <iostream>
#include "scanner.h"

//-----------------------------------------------------------------------------------
//                                 open
//-----------------------------------------------------------------------------------
int	scanner::open(string source) {
	f.open(source);
	if (f.fail()) {
		setError("open()", ' ', "Unable to open input file.");
		return 0;
	}
	return 1;
} // open()

  //-----------------------------------------------------------------------------------
  //                                close
  //-----------------------------------------------------------------------------------
void scanner::close() {
	f.close(); // close the source file
} // close()

  //-----------------------------------------------------------------------------------
  //                                 categorize
  //-----------------------------------------------------------------------------------
CHAR_CAT scanner::categorize(char c) {
	if (isalpha(c)) return ALPHA;
	if (isdigit(c)) return DIGIT;
	switch (c) {
	case -1:   return EOFL;
	case '\n': lineNo++; return EOL;
	case '\r': return EOL;
	case ' ':
	case '\t': return WHITESP;
	case '\'': return QUOTE;
	case '{':  return LBRACE;
	case '}':  return RBRACE;
	case '_':  return UNDERSC;
	case '.':  return DOTC;
	case '>':  return GTHANC;
	case '<':  return LTHANC;
	case ':':  return COLON;
	case '=':  return EQUAL;
	}
	const string psi = "+-/*[],;^()";
	if (psi.find(c) != string::npos) return SYMBOL;
	if (c >= ' ' && c < '~') return OTHER;

	// unidentified
	setError("categorize()", c, "Invalid character found in source.");
	return UNKNOWN;
} // categorize()

  //-----------------------------------------------------------------------------------
  //                                 getFSAerror
  //----------------------------------------------------------------------------------
string scanner::getFSAerror(CHAR_CAT cc, FSA_STATE state) {
	switch (state) {
	case START:
		if (cc == RBRACE) return "Beginning of comment expected.";
		return "Invalid beginning of lexeme.";
	case CMNT:  return "End of comment expected.";
	case SLIT:
		if (cc == EOL)  return "End of line found in string literal.";
		if (cc == EOFL) return "End of file found in string literal.";
		return "STATE=SLIT No transition from state found.";

	case SLITQ: return "Single quote expected.";
	case DECPT: return "Digit expected.";
	default:    return "Unknown error for STATE=" + FSA_STATE_STR[state] + ".";
	}
} // getFSAerror()

  //-----------------------------------------------------------------------------------
  //                                 getTrans
  //-----------------------------------------------------------------------------------
int scanner::getTrans(FSA_STATE currState, char c) {
	CHAR_CAT cc = categorize(c);
	if (is_error) return -1;
	char la = f.peek();
	CHAR_CAT lacc = categorize(f.peek());

	for (int i = 0; i < NUM_FSA_TRANS; i++) {
		if ((trans[i].from == currState) &&
			(trans[i].ccat == cc || trans[i].ccat == ANY) &&
			(trans[i].la == lacc || trans[i].la == ANY))
			return i;
	}
	setError("getTrans()", c, getFSAerror(cc, currState));
	return -1;
} // getTrans()

  //-----------------------------------------------------------------------------------
  //                                 getNextLexeme
  //-----------------------------------------------------------------------------------
string scanner::getNextLexeme() {
	FSA_STATE state = START;
	char c;
	int  transNo;
	string lex = "";

	while (state != HALT && !is_error) {
		c = f.get();
		transNo = getTrans(state, c);
		if (!is_error) {
			if (trans[transNo].to == ERR)
				setError("getNextLexeme()", c, getFSAerror(categorize(c), state));
			else {
				state = trans[transNo].to;
				if (trans[transNo].act == KEEP)
					lex += c;
				else if (trans[transNo].act == PUTB) {
					if (f.fail()) f.clear();
					f.putback(c);
				}
				// else discard c
			}
		}
	}

	if (is_error) return ""; else return lex;
} // getNextLexeme()

  //-----------------------------------------------------------------------------------
  //                                 resWordToTokenId
  //-----------------------------------------------------------------------------------
TOKENID scanner::resWordToTokenId(string lex) {
	for (unsigned int i = FIRST_TOK_RESWD_NDX; i < NUM_TOKENIDS; i++)
		if (lex == TOKENID_STR[i]) return ((TOKENID)i);
	return TOK_NONE; // not found, lex is not a Pascal reserved word or symbol
} // resWordToTokenId()

  //-----------------------------------------------------------------------------------
  //                                 upcase
  //-----------------------------------------------------------------------------------
string scanner::upcase(string s) {
	string x = s;
	for (unsigned int i = 0; i < s.length(); i++) x[i] = toupper(x[i]);
	return x;
} // resWordToTokenId()

  //-----------------------------------------------------------------------------------
  //                                 symCatToTokId
  //-----------------------------------------------------------------------------------
TOKENID scanner::symCatToTokId(int cat) {
	switch (cat) {
	case SYMCAT_IDENT:      return TOK_IDENT;
	case SYMCAT_INT_LIT:    return TOK_INT_LIT;
	case SYMCAT_REAL_LIT:   return TOK_REAL_LIT;
	case SYMCAT_STRING_LIT: return TOK_STRING_LIT;
	default:                return TOK_NONE;
	}
} // symCatToTokId()

  //-----------------------------------------------------------------------------------
  //                                 getNextToken
  //-----------------------------------------------------------------------------------
token scanner::getNextToken() {
	token t;
	TOKENID tid = TOK_NONE;
	symTblRef tref = NULL;
	string lex = getNextLexeme();

	if (is_error)
		tid = TOK_ERROR;
	else if (lex == "")
		tid = TOK_EOS;
	else {
		lex = upcase(lex);						// Pascal is not case sensitive
		tid = resWordToTokenId(lex);			// check if lex is a reserved word or symbol
		if (tid == TOK_NONE) {					// if not, its an identifier or literal
			tref = symbolTbl.insert(lex);		// insert into symbol table and keep reference
			tid = symCatToTokId(tref->getCategory());   // convert symbol category to token id
		}
	}
	t.setId(tid);
	t.setRef(tref);
	return t;
} // getNextToken()

  //-----------------------------------------------------------------------------------
  //                                 setError
  //-----------------------------------------------------------------------------------
void scanner::setError(string method, char c, string msg) {
	string sc = " ";
	sc[0] = c;
	error = "SCANERROR::" + method + "  Line=" + to_string(lineNo) + " Character=";
	int ascii = (int)c;
	if (ascii <= 32 || ascii >= 127)
		error += "UNPRINTABLE (";
	else
		error += "'" + sc + "' (";
	error += to_string(ascii) + ")\n" + msg;
	is_error = true;
} // setError()


