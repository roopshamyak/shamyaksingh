//------------------------------------------------
//           test program for project 2
//------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "parser.h"
#include "grammar.h"
//#include "prints.h"
using namespace std;

int  main(int argc, char** argv) {
	parser p;
	string fileName, errMsg;

	// get file name from command line, or ask user
	if (argc > 1)
		fileName = argv[1];
	else {
		cout << "Enter file name: ";
		getline(cin, fileName);
	}

	// open file in scanner
	errMsg = p.compile(fileName);
	if (errMsg != "") cout << errMsg << endl;

	return 0;
}
