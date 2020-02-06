#include <iostream>
#include <iomanip>
#include "token.h"
#include "grammar.h"

//---------------------------------------------------------------------------------------
//                                printProduction
//---------------------------------------------------------------------------------------
void printProduction(int n) {
	if (n < 0 || n >= GR_NUMPRODS) { cout << "printProduction: invalid prod number: " << n << endl; abort(); }
	string RHS, sset;
	RHS = "";
		for (int j = GR_FIRST_RHS; j <= GR_LAST_RHS; j++)
		if (PROD[n][j] != E)
			RHS = RHS + " " + TOKENID_STR[PROD[n][j]];
	sset = "{";
	for (int j = GR_FIRST_SELSET; j <= GR_LAST_SELSET; j++)
		if (PROD[n][j] != E)
			sset = sset + " " + TOKENID_STR[PROD[n][j]];
	sset += " }";
	std::cout << right << setw(2) << n << " "
		<< left << setw(18) << TOKENID_STR[PROD[n][0]] << " --> "
		<< setw(33) << RHS << "   " << sset << endl;
} // printProduction()

//---------------------------------------------------------------------------------------
//                                printGrammar
//---------------------------------------------------------------------------------------
void printGrammar() {

	for (int i = 0; i < GR_NUMPRODS; i++) {
		printProduction(i);
	}
	std::cout << endl;
}

//---------------------------------------------------------------------------------------
//                                printTokenIds
//---------------------------------------------------------------------------------------
void printTokenIds() {
	for (int i = 0; i < NUM_TOKENIDS; i++)
		std::cout << right << setw(3) << i << " " << left << TOKENID_STR[i] << endl;
	const int NUM_TOKENIDS = 97;	    // number of token id strings in the list
	const int FIRST_TOK_RESWD_NDX = 7;  // index of the first reserved word/symbol in the list
	const int LAST_TOK_RESWD_NDX = 77;
	std::cout << "NUM_TOKEN_IDS       = " << NUM_TOKENIDS << endl;
	std::cout << "FIRST_TOK_RESWD_NDX = " << FIRST_TOK_RESWD_NDX << endl;
	std::cout << "LAST_TOK_RESWD_NDX  = " << LAST_TOK_RESWD_NDX << endl << endl;
}