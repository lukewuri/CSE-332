// Lab1.cpp : Defines the entry point for the console application.
//name:Luke Wuri
//e-mail: lwuri@wustl.edu
//user: lwuri
//ID:445002
#include "stdafx.h"
#include "lab1common.h"
#include "gamepiece.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "gameboard.h"
#include <cctype>
#include <sstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;
//use "_CRT_SECURE_NO_WARNINGS" in Preprocessor Definitions in project properties to make 
//the lowercase function work... it seems that the strncpy function is faulty under default settings


string lowercase(string a) {
	char arr[100];
	strcpy(arr, a.c_str()); //copies string into our char array
	string lowerstring;
	int conversion ='A' -'a'; //difference between capital and lower case
	char b;
	for (unsigned int i = 0; i < strlen(arr); i++) {//iterate through our string a
		//#www.cplusplus.com/forum/general/837/ was used for inspiration 
		strncpy(&b, arr + i, 1); //(destination, source, num of char)
		if (b>='A' && b<='Z') {//check if capital letter 
			b = b - conversion;
			memcpy(arr + i, &b, 1);
		}
	}
	lowerstring = arr; //convert back into string
	return lowerstring;
}

int ReadFile(vector<string>& lines, char* FileName) {//taken from my lab0 for reference
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

int main(int argc, char * argv[]){ //argc is arg count
	ifstream stream;
	unsigned int x = 0;
	unsigned int y = 0;
	vector<game_piece> printout;
	
	if (argc = 2) {//there can only be one argument (aside from program name)
		stream.open(argv[1]);// file location/name
		dimension(stream, x, y);//get dimensions
		cout << x << y;
		readingFile(stream, printout,x,y);
		print(printout, x, y);
	
	}
}

