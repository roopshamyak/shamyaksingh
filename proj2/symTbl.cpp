#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "symTbl.h"

//------------------- constructor ------------------
symTbl::symTbl() {
	for (int i = 0; i < SYMTBL_NUM_BUCKETS; i++)
		bucket[i] = NULL;
} // constructor

//--------------------  insert  -------------------
symTblRef symTbl::insert(string newlex) {
	symTblRef s = search(newlex);
	if (!s) {
		int hv = hash(newlex);
		s = new symbol;
		s->setLex(newlex);
		s->next = bucket[hv];
		bucket[hv] = s;
	}
	return s;
} // insert()

//--------------------- hash ---------------------
int symTbl::hash(string lex) {
	int sum = 0;
	for (int i = 0; i < (int)lex.length(); i++) {
		sum += (int) lex[i];
	}
	return sum % SYMTBL_NUM_BUCKETS;
} // hash()

//---------------------- search ---------------------
symTblRef symTbl::search(string search4) {
	int hv = hash(search4);
	symTblRef p = bucket[hv];
	while (p) {
		if (p->lexeme == search4)
			return p;
		p = p->next;
	}
	return NULL;
} // search()

//---------------------- print ---------------------
void symTbl::print() {
	int numEntries = 0;  
	cout << "---------- SYMBOL TABLE ------------\n";
	for (int i = 0; i < SYMTBL_NUM_BUCKETS; i++) {
		// only print bucket if it has an entry
		if (bucket[i] != NULL) {
			// print first entry in this bucket with bucket #
			symTblRef p = bucket[i];
			cout << "[" << setw(3) << i << "]: ";
			cout << "cat=" << p->getCategory()
				<< "  dtype=" << p->getDataType()
				<< "  lex=" << p->getLex() << endl;
			numEntries++;
			p = bucket[i]->next;

			// print all other entries in this bucket
			while (p) {
				cout << "       cat=" << p->getCategory()
					<< "  dtype=" << p->getDataType()
					<< "  lex=" << p->getLex() << endl;
				numEntries++;
				p = p->next;
			} // while more entries in bucket
		} // if bucket not empty
	} // for all buckets
	cout << "------------------------------------\n";
	cout << "Number of entries: " << numEntries << endl << endl;
	cout << "Press any key to continue..";
	getchar();
} // print()