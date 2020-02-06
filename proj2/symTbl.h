#pragma once
//--------------------------------------------------
//                      class symTbl
//--------------------------------------------------
// A symbol table for the compiler. It maintains a
// list of identifiers and literals found in the 
// source file. 
// It is implemented as a Hash Table to save space
// and speed lookups.
// The has table is an array of symbol pointers.
// Each element of the array is a pointer to the head
//      of a linked list of dynamically-allocated symbols.
// The hash function should return a value between
// 0 and (#buckets-1), which is the range of the array 
// indices.
//--------------------------------------------------
#include "symbol.h"

const int SYMTBL_NUM_BUCKETS = 1000;

class symTbl {
public:
	symTbl();
	void      print();
	symTblRef search(string lex);
	symTblRef insert(string newlex);
private:
	symTblRef bucket[SYMTBL_NUM_BUCKETS];
	int hash(string s);
	// other private methods may be added if needed.
};