#pragma once
#include <string>
using namespace std;

// FSA states 
enum FSA_STATE {
	HALT, START, CMNT, ERR, ID, INT, DECPT, FRAC, SLIT, SLITQ, GTHAN, LTHAN, DOT
};
const int NUM_FSA_STATES = 13;
const string FSA_STATE_STR[NUM_FSA_STATES] = {
	"HALT", "START", "CMNT", "ERR", "ID", "INT", "DECPT", "FRAC", "SLIT", "SLITQ", 
	"GTHAN", "LTHAN", "DOT"
};

// FSA character categories
enum CHAR_CAT {
	UNKNOWN, ANY, WHITESP, EOFL, EOL, LBRACE, RBRACE, ALPHA, DIGIT, UNDERSC, DOTC, 
	QUOTE, GTHANC, LTHANC, COLON, EQUAL, SYMBOL, OTHER
};
const int NUM_CHAR_CATS = 18;
const string CHAR_CAT_STR[NUM_CHAR_CATS] = {
	"UNKNOWN", "ANY", "WHITESP", "EOFL", "EOL", "LBRACE", "RBRACE", "ALPHA", "DIGIT", 
	"UNDERSC", "DOTC","QUOTE", "GTHANC", "LTHANC", "COLON", "EQUAL", "SYMBOL", "OTHER"
};

// FSA actions
enum ACTION { KEEP, DISC, PUTB };
const int NUM_FSA_ACTIONS = 3;
const string ACTION_STR[NUM_FSA_ACTIONS] = { "KEEP","DISC","PUTB" };

// A Transition between two states based on a character category and look ahead,
// specifying the TO state and the action to take with the character
class transition {
public:
	FSA_STATE from;
	FSA_STATE to;
	CHAR_CAT  ccat;
	CHAR_CAT  la;
	ACTION    act;
};

// FSA Transitions 
const int NUM_FSA_TRANS = 41;
const transition trans[NUM_FSA_TRANS] = {
	{ START, START, WHITESP, ANY,   DISC },
	{ START, START, EOL,     ANY,   DISC },
	{ START, HALT,  EOFL,    ANY,   DISC },
	{ START, CMNT,  LBRACE,  ANY,   DISC },
	{ CMNT,  ERR,   EOFL,    ANY,   DISC },
	{ CMNT,  START, RBRACE,  ANY,   DISC },
	{ CMNT,  CMNT,  ANY,     ANY,   DISC },
	{ START, ID,    ALPHA,   ANY,   KEEP },
	{ ID,    ID,    ALPHA,   ANY,   KEEP },
	{ ID,    ID,    DIGIT,   ANY,   KEEP },
	{ ID,    ID,    UNDERSC, ANY,   KEEP },
	{ ID,    HALT,  ANY,     ANY,   PUTB },
	{ START, INT,   DIGIT,   ANY,   KEEP },
	{ INT,   INT,   DIGIT,   ANY,   KEEP },
	{ INT,   HALT,  DOTC,    DOTC,  PUTB },
	{ INT,   DECPT, DOTC,    ANY,   KEEP },
	{ INT,   HALT,  ANY,     ANY,   PUTB },
	{ DECPT, FRAC,  DIGIT,   ANY,   KEEP },
	{ DECPT, ERR,   ANY,     ANY,   KEEP },
	{ FRAC,  FRAC,  DIGIT,   ANY,   KEEP },
	{ FRAC,  HALT,  ANY,     ANY,   PUTB },
	{ START, SLIT,  QUOTE,   ANY,   KEEP },
	{ SLIT,  SLITQ, QUOTE,   QUOTE, KEEP },
	{ SLIT,  HALT,  QUOTE,   ANY,   KEEP },
	{ SLIT,  ERR,   EOFL,    ANY,   KEEP },
	{ SLIT,  ERR,   EOL,     ANY,   KEEP },
	{ SLIT,  SLIT,  ANY,     ANY,   KEEP },
	{ SLITQ, SLIT,  QUOTE,   ANY,   KEEP },
	{ START, GTHAN, GTHANC,  ANY,   KEEP },
	{ GTHAN, HALT,  EQUAL,   ANY,   KEEP },
	{ GTHAN, HALT,  ANY,     ANY,   PUTB },
	{ START, GTHAN, COLON,   ANY,   KEEP },
	{ START, LTHAN, LTHANC,  ANY,   KEEP },
	{ LTHAN, HALT,  EQUAL,   ANY,   KEEP },
	{ LTHAN, HALT,  GTHANC,  ANY,   KEEP },
	{ LTHAN, HALT,  ANY,     ANY,   PUTB },
	{ START, DOT,   DOTC,    ANY,   KEEP },
	{ DOT,   HALT,  DOTC,    ANY,   KEEP },
	{ DOT,   HALT,  ANY,     ANY,   PUTB },
	{ START, HALT,  SYMBOL,  ANY,   KEEP },
	{ START, HALT,  EQUAL,   ANY,   KEEP },
};
