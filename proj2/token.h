#pragma once
//-------------------------------------------------------------
//                      class token
//--------------------------------------------------------------
// A token is a tuple (pair of values) representing a
// single word or symbol from the source file. Tokens
// are extracted from the source by the scanner and 
// delivered to the parser. The two values are:
// Token ID: an integer (enum) representing the 
//           kind of token, including:
//           - a string/int/real LITTERAL
//           - an IDENTIFIER
//           - a RESERVED WORD OR SYMBOL of the language
//           - for processing purposes: NONE(empty), 
//                 END OF SOURCE or ERROR
// Symbol Table Ref.: a pointer to a symbol table entry
//           - NULL for a Reserved word or symbol 
//           - NOT NULL for an Identifier or Literal
// Also included:
// - an enumeration listing all possible values of a TOKENID
// - a parallel array of TOKENID strings for debugging and
//   error messsages.
// These include a list of all reserved words/symbols in
// the language, as well as Non-Terminals from the Pascal Grammar
//---------------------------------------------------------------------------------
#include "symTbl.h"

// Token Identifiers, including reserved words and symbols, as well as Parser Non-Terminals
enum TOKENID {
	TOK_NONE, TOK_ERROR, TOK_EOS, TOK_INT_LIT, TOK_REAL_LIT, TOK_STRING_LIT, TOK_IDENT, 
	TOK_SEMIC, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_LBRAC, TOK_RBRAC, TOK_LPAREN, TOK_RPAREN,
	TOK_COMMA, TOK_COLON, TOK_HAT, TOK_DOT, TOK_LTHAN, TOK_LTHAN_EQ, TOK_GTHAN, TOK_GTHAN_EQ, 
	TOK_NOT_EQ, TOK_EQUAL, TOK_ASSIGN, TOK_DOTDOT,
	TOK_AND, TOK_ARRAY, TOK_BEGIN, TOK_BOOLEAN, TOK_CASE, TOK_CHAR, TOK_CONST, TOK_DIV, TOK_DO,
	TOK_DOWNTO, TOK_ELSE, TOK_END, TOK_EOF, TOK_FALSE, TOK_FILE, TOK_FOR, TOK_FUNCTION, TOK_GOTO,
	TOK_IF, TOK_IN, TOK_INTEGER, TOK_LABEL, TOK_MAXINT, TOK_MOD, TOK_NIL, TOK_NOT, TOK_OF, TOK_OR,
	TOK_OUTPUT, TOK_PACK, TOK_PACKED, TOK_PROCEDURE, TOK_PROGRAM, TOK_READ, TOK_READLN, TOK_REAL,
	TOK_RECORD, TOK_REPEAT, TOK_SET, TOK_STRING, TOK_THEN, TOK_TO, TOK_TRUE, TOK_TYPE, TOK_UNTIL, TOK_VAR,
	TOK_WHILE, TOK_WITH, TOK_WRITE, TOK_WRITELN,
	TOK_N_EPSILON, TOK_N_PROGRAM, TOK_N_DECLARATIONS, TOK_N_CMPD_STMT, TOK_N_ID_LIST, TOK_N_IDLIST_END,
	TOK_N_TYPE, TOK_N_OPT_STMTS, TOK_N_STMT_LIST, TOK_N_STMT, TOK_N_STMT_LIST_END,
	TOK_N_EXPR, TOK_N_COND, TOK_N_RELOP, TOK_N_VAL, TOK_N_EXPR_END,
	TOK_N_ARITH_OP, TOK_N_SIGN, TOK_DEFAULT
};

const int NUM_TOKENIDS = 97;	    // number of token id strings in the list
const int FIRST_TOK_RESWD_NDX = 7;  // index of the first reserved word/symbol in the list
const int LAST_TOK_RESWD_NDX = 77;  // index of the last  reserved word/symbol in the list
const int FIRST_NON_TERMINAL = 78;  // index of the first Non-Terminal Token Id
const int LAST_NON_TERMINAL = 96;   // index of the last  Non-Terminal Token Id
const string TOKENID_STR[NUM_TOKENIDS] = {
	// Special Token Ids - not Pascal Reserved Words or Symbols
	// TOK_EOS=End of Source, when getNextLex returns "". Since EOF is a Res. Wd., can't use TOK_EOF
	"TOK_NONE", "TOK_ERROR", "TOK_EOS", "TOK_INT_LIT", "TOK_REAL_LIT", "TOK_STRING_LIT", "TOK_IDENT",

	// Pascal Symbols
	";", "+", "-", "*", "/", "[", "]", "(", ")",   "," , ":", "^", ".", "<", "<=", ">", ">=", 
	"<>", "=", ":=", "..",

	// Pascal Reserved Words
	"AND", "ARRAY", "BEGIN", "BOOLEAN", "CASE", "CHAR", "CONST", "DIV", "DO",
	"DOWNTO", "ELSE", "END", "EOF", "FALSE", "FILE", "FOR", "FUNCTION", "GOTO",
	"IF", "IN", "INTEGER", "LABEL", "MAXINT", "MOD", "NIL", "NOT", "OF", "OR",
	"OUTPUT", "PACK", "PACKED", "PROCEDURE", "PROGRAM", "READ", "READLN", "REAL",
	"RECORD", "REPEAT", "SET", "STRING", "THEN", "TO", "TRUE", "TYPE", "UNTIL", "VAR",
	"WHILE", "WITH", "WRITE", "WRITELN",

	// Parser Non-Terminals
	"N_EPSILON", "N_PROGRAM", "N_DECLARATIONS", "N_CMPD_STMT", "N_ID_LIST", "N_IDLIST_END",
	"N_TYPE", "N_OPT_STMTS", "N_STMT_LIST", "N_STMT", "N_STMT_LIST_END",
	"N_EXPR", "N_COND", "N_RELOP", "N_VAL", "N_EXPR_END",
	"N_ARITH_OP", "N_SIGN", "TOK_DEFAULT"
};

class token {
public:
	symTblRef getRef();
	TOKENID   getId();
	void      setId(TOKENID tid);
	void      setRef(symTblRef tref);
	string    getPrintString();
private:
	TOKENID   id = TOK_NONE;   // identifies the type of token, including reserved words/symbols
	symTblRef ref = NULL;      // pointer to an entry in the symbol table; NULL for res. words
};