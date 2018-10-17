#include "stdafx.h"
#include "gameboard.h"
#include "lab1common.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
using namespace std;


int dimension(ifstream & a, unsigned int& x, unsigned int& y) {//step 11, extract the dimensions from the first line
	//confused me initially why we needed x and y as parameters/input, but we are setting the values sfor x and y through this function.
	string line; //will hold the line with the dimensions
	unsigned int c; //intermediate placeholder

	int b = 0;
	//getline, and both extraction functions must be checked if they return true
	if (getline(a, line)) { //next we need to wrap string variable in an "input string stream"
		stringstream stringstream(line);

		if (stringstream >> c) {//extract first value,x
			x = c;
			b = 5;
		}
		if ((stringstream >> c) && (b == 5)) {//extract right value,y. Will only go into here if b value was changed in the above if statement
			y = c;
			return Success;
		}

		return CannotExtractDimension;
	}
	return CannotExtractDimension;
}

int readingFile(ifstream & a, vector<game_piece> & pos, unsigned int dimx, unsigned int dimy) {//step 12
	bool linesgood;
	string line;
	string interline;
	vector<string> lines; //holds the entire file of strings
	while (getline(a, line)) {// gets line from 'a' into 'line'
		stringstream stringstream(line); //allow for operation on line
		for (int i = 0;i < 5; i++) {//5 columns
			(stringstream >> interline);//extract 'line''s value into interline
			lines.push_back(interline); //push into our lines vector
		}
		if (lines.size() == 5) {
			piece_color color = color2(lines[0]);
			unsigned int x = stoi(lines[3]);
			unsigned int y = stoi(lines[4]);
			int cordcalc = ((dimx)*(y)+x); //what
			if ((color = invalid) || (x > dimx) || (y > dimy)) {
				linesgood = false;
			}
			else {
				pos[cordcalc] = { color,lines[1], lines[2] };
				linesgood = true;
			}
		}
		if (linesgood) {
			return Success;
		}
		else {
			return InvalidExtract;
		}
		
	}
	return GetLineFail;
}

int print(const vector<game_piece>& a, unsigned int x, unsigned int y) {
	for (unsigned int i = 0; i < a.size(); i++) {
		cout << a[i].display << "-";
		if ((i + 1) % x == 0) {
			cout << endl;
		}
	}
	return Success;
}