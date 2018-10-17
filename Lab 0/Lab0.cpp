// Lab0.cpp : Defines the entry point for the console application.
//name:Luke Wuri
//e-mail: lwuri@wustl.edu
//user: lwuri
//ID:445002
#include "arraystuff.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int ProgramNameIndex = 0;
int InputFileNameIndex = 1;
int NumOfArguments = 2;

int Success = 0;
int CannotOpenFile = 1;
int TwoErrors = 2;

bool letterChecker(const string& a) {
	bool letter = false;
	for (unsigned int i = 0; i < a.size(); i++) {
		if (!(isdigit(a[i]))){
			letter = true;
		}
		
	}return letter;
}

int ReadFile(vector<string>& lines, char* FileName) {
	ifstream input;
	input.open(FileName);
	string line; //string with all the lines

	if (!(input.good())) {// file can't be opened
		return CannotOpenFile;
	}
	while (input >> line) {
		lines.push_back(line);
	}
	return Success;
}

int errorFunction (char * argv){
	cout << "Lab 0 Help Message for:" << argv[0] << endl;
	cout << "There were too many arguments.";
	return NumOfArguments;
}



int main(int argc, char * argv[])
{
	vector<string> lines;
	vector<int> stringints; //Vector of ints that we will print
	string ProgramName(argv[ProgramNameIndex]);

	int x;
	int value = ReadFile(lines, argv[InputFileNameIndex]);

	for (unsigned int i = 0; i < lines.size(); i++) {
		if (!(letterChecker(lines[i]))) {
			istringstream convert(lines[i]);
			convert >> x;
			stringints.push_back(x);
		}
	}

	for (unsigned int k = 0; k < lines.size(); k++) {
		if (letterChecker(lines[k])) {
			cout << lines[k] << endl;
		}
		}

		cout << "....." << endl;
		for (unsigned int k = 0; k < stringints.size(); k++) {
			cout << stringints[k] << endl;
		}
	return 0;

}



