#pragma once
#include <iostream>
#include <iomanip>
#include "token.h"
//------------------------------------------------------------------------
//                             grammar.h
//------------------------------------------------------------------------
// Defines the Pascal Grammar used by the Parser
// Implemented as a 2D array of TOKENID where:
// - each row represents a production from the grammar
// - column  0:    Non-Terminal on the Left Hand Side
// - columns 1-6:  Terminals/Non-Terminals on the Right Hand Side
//                 When fewer than 6, right-padded with E (Epsilon)
// - columns 7-10: The Select Set, right-padded with E when fewer than 4
//                 TOK_DEFAULT in column 7 means "default" production
//------------------------------------------------------------------------
const TOKENID E = TOK_N_EPSILON;  // just to shorten/de-clutter a bit

const int GR_NUMPRODS = 41;			// total number of productions in grammar
const int GR_TABLE_WIDTH = 11;		// total number of columns in table
const int GR_LHS = 0;				// index of LHS Non-Terminal
const int GR_FIRST_RHS = 1;			// index of first Term/NT of RHS
const int GR_LAST_RHS = 6;          // index of last Term/NT of RHS
const int GR_FIRST_SELSET = 7;      // index of first member of Select Set
const int GR_LAST_SELSET = 10;      // index of last member of Select Set

const TOKENID PROD[GR_NUMPRODS][GR_TABLE_WIDTH] = {
	{TOK_N_PROGRAM, TOK_PROGRAM, TOK_IDENT, TOK_SEMIC, TOK_N_DECLARATIONS, TOK_N_CMPD_STMT, TOK_DOT, TOK_DEFAULT, E, E, E },
	{TOK_N_ID_LIST, TOK_IDENT, TOK_N_IDLIST_END, E,E,E,E, TOK_DEFAULT, E,E,E },
	{TOK_N_IDLIST_END, TOK_COMMA, TOK_N_ID_LIST, E,E,E,E, TOK_COMMA, E,E,E },
	{TOK_N_IDLIST_END, E,E,E,E,E,E, TOK_DEFAULT, E,E,E },
	{TOK_N_DECLARATIONS, TOK_VAR, TOK_N_ID_LIST, TOK_COLON, TOK_N_TYPE, TOK_SEMIC, TOK_N_DECLARATIONS, TOK_VAR, E,E,E },
	{TOK_N_DECLARATIONS, E,E,E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_TYPE, TOK_INTEGER, E,E,E,E,E, TOK_INTEGER, E,E,E},
	{TOK_N_TYPE, TOK_REAL, E,E,E,E,E, TOK_REAL, E,E,E},
	{TOK_N_TYPE, TOK_STRING, E,E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_CMPD_STMT, TOK_BEGIN, TOK_N_OPT_STMTS, TOK_END, E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_OPT_STMTS, E,E,E,E,E,E, TOK_END, E,E,E},
	{TOK_N_OPT_STMTS, TOK_N_STMT_LIST, E,E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_STMT_LIST, TOK_N_STMT, TOK_N_STMT_LIST_END, E,E,E,E, TOK_DEFAULT, E,E,E },
	{TOK_N_STMT_LIST_END, TOK_SEMIC, TOK_N_STMT_LIST, E,E,E,E, TOK_SEMIC, E,E,E},
	{TOK_N_STMT_LIST_END, E,E,E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_STMT, TOK_IDENT, TOK_ASSIGN, TOK_N_EXPR, E,E,E, TOK_IDENT, E,E,E},
	{TOK_N_STMT, TOK_IF, TOK_N_COND, TOK_THEN, TOK_N_STMT, TOK_ELSE, TOK_N_STMT,  TOK_IF, E,E,E},
	{TOK_N_STMT, TOK_WHILE, TOK_N_COND, TOK_DO, TOK_N_STMT, E,E, TOK_WHILE, E,E,E},
	{TOK_N_STMT, TOK_N_CMPD_STMT, E,E,E,E,E, TOK_DEFAULT, E,E,E },
	{TOK_N_COND, TOK_N_EXPR, TOK_N_RELOP, TOK_N_EXPR, E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_EXPR, TOK_N_VAL, TOK_N_EXPR_END, E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_EXPR_END, TOK_N_ARITH_OP, TOK_N_VAL, TOK_N_EXPR_END, E,E,E, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH },
	{TOK_N_EXPR_END, E,E,E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_ARITH_OP, TOK_PLUS, E,E,E,E,E, TOK_PLUS, E,E,E},
	{TOK_N_ARITH_OP, TOK_MINUS, E,E,E,E,E, TOK_MINUS, E,E,E},
	{TOK_N_ARITH_OP, TOK_STAR, E,E,E,E,E, TOK_STAR, E,E,E},
	{TOK_N_ARITH_OP, TOK_SLASH, E,E,E,E,E, TOK_DEFAULT, E,E,E,},
	{TOK_N_RELOP, TOK_LTHAN, E,E,E,E,E, TOK_LTHAN, E,E,E},
	{TOK_N_RELOP, TOK_LTHAN_EQ, E,E,E,E,E, TOK_LTHAN_EQ, E,E,E },
	{TOK_N_RELOP, TOK_GTHAN, E,E,E,E,E, TOK_GTHAN, E,E,E },
	{TOK_N_RELOP, TOK_GTHAN_EQ, E,E,E,E,E, TOK_GTHAN_EQ, E,E,E },
	{TOK_N_RELOP, TOK_NOT_EQ, E,E,E,E,E, TOK_NOT_EQ, E,E,E },
	{TOK_N_RELOP, TOK_EQUAL, E,E,E,E,E, TOK_DEFAULT, E,E,E },
	{TOK_N_VAL, TOK_IDENT, E,E,E,E,E, TOK_IDENT, E,E,E},
	{TOK_N_VAL, TOK_INT_LIT, E,E,E,E,E, TOK_INT_LIT, E,E,E},
	{TOK_N_VAL, TOK_REAL_LIT, E,E,E,E,E, TOK_REAL_LIT, E,E,E},
	{TOK_N_VAL, TOK_STRING_LIT, E,E,E,E,E, TOK_STRING_LIT, E,E,E},
	{TOK_N_VAL, TOK_LPAREN, TOK_N_EXPR, TOK_RPAREN, E,E,E, TOK_LPAREN, E,E,E},
	{TOK_N_VAL, TOK_N_SIGN, TOK_N_VAL, E,E,E,E, TOK_DEFAULT, E,E,E},
	{TOK_N_SIGN, TOK_PLUS, E,E,E,E,E, TOK_PLUS, E,E,E},
	{TOK_N_SIGN, TOK_MINUS, E,E,E,E,E, TOK_DEFAULT, E,E,E}
};


