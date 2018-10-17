//Author: Brian Halsell

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Lab4.h"
#include "GamePieces.h"
using namespace std;

string enumToString(piece_color myEnum) {
	vector<string> myVector = { "red", "black", "white", "invalidcolor", "nocolor" };
	return myVector[myEnum];
}

piece_color stringToEnum(string myString) {
	if (myString == "red") {
		return red;
	}
	else if (myString == "black") {
		return black;
	}
	else if (myString == "white") {
		return white;
	}
	else if (myString == " ") {
		return noColor;
	}
	else {
		return invalidColor;
	}
}

Piece::Piece(piece_color color, string name, string display)
	: color_(color), name_(name), display_(display) {}

