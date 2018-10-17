//Author: Brian Halsell brianhalsell@wustl.edu, Luke Wuri, Mike Warfield
//Source file for MagicSquareGame

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "MagicSquareGame.h"
#include "Lab4.h"
#include "GamePieces.h"
#include "NineAlmondsGame.h"
using namespace std;

//Constructor for Magic Square Game Class
MagicSquareGame::MagicSquareGame()
	: availPieces() {
	xDim = 3;
	yDim = 3;
	//create array to store whether pieces are avaiable to play
	for (int i = 0; i < 10; i++) {
		availPieces.push_back(true);
	}

	//check save file
	ifstream ifs("MagicSquareGame.txt");
	if (!(ifs.is_open())) {
		throw "Save file could not be opened";
	}
	string myVal;
	if (!(ifs >> myVal)) {
		throw "Could not read save file";
	}
	if (myVal != "NODATA") {
		//remove dims and line breaks
		ifs >> myVal;
		ifs >> myVal;
		ifs >> myVal;

		for (int i = 0; i < yDim; ++i) {
			for (int j = 0; j < xDim; ++j) {
				string currPiece;
				int currInt;
				ifs >> currPiece;
				currInt = stringToInt(currPiece);
				if (currInt > 0 && currInt < xDim*yDim + 1) {
					string name = currPiece;
					string display = currPiece;
					Piece tempPiece(noColor, name, display);
					piecesVect.push_back(tempPiece);
					availPieces[currInt] = false;
				}
				else {
					string name = "";
					string display = " ";
					Piece tempPiece(noColor, name, display);
					piecesVect.push_back(tempPiece);
				}
			}
		}
	}
	else {
		//create empty spaces for board
		for (int i = 0; i < 9; ++i) {
			string name = "";
			string display = " ";
			Piece tempPiece(noColor, name, display);
			piecesVect.push_back(tempPiece);
		}
	}
}

//Overloaded prompt
int MagicSquareGame::prompt(unsigned int& a) {
	bool validCoord = false;
	//Ask for number to place or x cord or y cord
	while (!validCoord) {
		string myInput;
		getline(cin, myInput);
		if (myInput == "quit") {
			return quit;
		}
		//extract value from input
		string modifiedStr;
		//will take only first coord
		replace(myInput.begin(), myInput.end(), ',', ' ');
		istringstream myISStream(myInput);
		unsigned int x;
		if (myISStream >> x) {
			if (x >= 0 && x < piecesVect.size() + 1) {
				a = x;
				validCoord = true;
			}
		}
		if (!validCoord) {
			cout << "Invalid input given." << endl;
		}
	}
	return 0;
}

//ostream operator to print board
ostream& operator<< (ostream& myOut, MagicSquareGame& myGame) {
	int x = myGame.xDim;
	int y = myGame.yDim;
	setw(myGame.len);
	for (int i = y - 1; i >= 0; --i) {
		string myString = to_string(i);
		for (int j = 0; j < x; ++j) {
			int currentIndex = i * x + j;
			myString = myString + " " + myGame.piecesVect[currentIndex].display_;
		}
		cout << myString << endl;
	}
	string finalStr = "X";
	for (int i = 0; i < x; ++i) {
		finalStr = finalStr + " " + to_string(i);
	}
	cout << finalStr << endl;
	//print string containing available pieces
	string availPiecesStr;
	for (unsigned int i = 1; i < myGame.availPieces.size(); ++i) {
		if (myGame.availPieces[i] == true) {
			availPiecesStr = availPiecesStr + " ";
			availPiecesStr = availPiecesStr + to_string(i);
		}
	}
	cout << "Available Pieces:" << availPiecesStr << endl;
	return myOut;
}

//method to find if game is won
bool MagicSquareGame::done() {
	for (unsigned int i = 1; i < availPieces.size(); ++i) {
		if (availPieces[i]) {
			return false;
		}
	}

	//check all rows/columns/diagnols to make sure they are equal to 15
	int sumLeftCol = 0, sumMidCol = 0, sumRightCol = 0;
	for (unsigned int i = 0; i < piecesVect.size(); i = i + piecesVect.size() / 3) {
		sumLeftCol += stringToInt(piecesVect[i].display_);
		sumMidCol += stringToInt(piecesVect[i + 1].display_);
		sumRightCol += stringToInt(piecesVect[i + 2].display_);
	}
	if (sumLeftCol != 15 || sumMidCol != 15 || sumRightCol != 15) {
		return false;
	}

	int sumBotRow = 0, sumMidRow = 0, sumTopRow = 0;
	for (unsigned int i = 0; i < piecesVect.size() / 3; i++) {
		sumBotRow += stringToInt(piecesVect[i].display_);
		sumMidRow += stringToInt(piecesVect[i + piecesVect.size() / 3].display_);
		sumTopRow += stringToInt(piecesVect[i + 2 * piecesVect.size() / 3].display_);
	}
	if (sumBotRow != 15 || sumMidRow != 15 || sumTopRow != 15) {
		return false;
	}

	int diag1 = 0, diag2 = 0;
	diag1 = stringToInt(piecesVect[0].display_) + stringToInt(piecesVect[4].display_) + stringToInt(piecesVect[8].display_);
	diag2 = stringToInt(piecesVect[2].display_) + stringToInt(piecesVect[4].display_) + stringToInt(piecesVect[6].display_);
	if (diag1 != 15 || diag2 != 15) {
		return false;
	}
	try {
		deleteSave();
	}
	catch (char const* e) {
			cout << e << endl;
	}
	return true;
}

//method check to see if no avaiable moves are left but game is not won
bool MagicSquareGame::stalemate() {
	for (unsigned int i = 1; i < availPieces.size(); ++i) {
		if (availPieces[i]) {
			return false;
		}
	}
	try {
		deleteSave();
	}
	catch (char const* e) {
		cout << e << endl;
	}
	//return true if game is not won
	return !done();
}

//method to run one turn of the game
int MagicSquareGame::turn() {
	int validMove = 1;
	print();
	while (validMove) {
		unsigned int a = 0;
		unsigned int b = 0;
		unsigned int myPiece = 0;
		int validX = 1;
		int validY = 1;
		int validPiece = 1;
		//get valid x coord
		while (validX) {
			cout << "Input x coordinate or type quit to quit" << endl;
			validX = prompt(a);
			//check for quit
			if (validX == game_quit) {
				return game_quit;
			}
			if ((int)a >= xDim) {
				cout << "Not within board bounds" << endl;
				validX = 1;
			}
		}
		//get valid y coord
		while (validY) {
			cout << "Input y coordinate or type quit to quit" << endl;
			validY = prompt(b);
			if (validY == game_quit) {
				return game_quit;
			}
			if ((int)b >= yDim) {
				cout << "Not within board bounds" << endl;
				validY = 1;
			}

		}
		//get valid value for piece to place
		while (validPiece) {
			cout << "Input piece value or type quit to quit" << endl;
			validPiece = prompt(myPiece);
			if (validPiece == game_quit) {
				return game_quit;
			}
			//dont allow 0 piece to be played
			if (myPiece == 0) {
				cout << "Invalid input" << endl;
				validPiece = 1;
			}
		}
		//check if piece exists at that location
		if ((piecesVect[a + b * yDim].name_ != "")) {
			cout << "Piece exists at that location" << endl;
		}
		//check if piece to play is available
		else if (!availPieces[myPiece]) {
			cout << "Piece already played" << endl;
		}
		//valid move
		else {
			unsigned int index = xDim * b + a;
			string name = to_string(myPiece);
			string display = to_string(myPiece);
			Piece tempPiece(noColor, name, display);
			piecesVect[index] = tempPiece;
			availPieces[myPiece] = false;
			validMove = 0;
		}
	}
	return 0;
}

int MagicSquareGame::save(int turns) {
	ofstream ofs("MagicSquareGame.txt");
	if (!ofs.is_open()) {
		throw "Save file could not be opened";
	}
	if (!(ofs << "MagicSquareGame" << endl)) {
		throw "Cannot write to save file";
	}
	ofs << xDim << " " << yDim << endl;
	ofs << turns << endl;
	for (int i = 0; i < yDim; ++i) {
		string myString;
		for (int j = 0; j < xDim; ++j) {
			int currentIndex = i * xDim + j;
			//modify white space to , as that is easier to work with through fstreams
			string myDis = piecesVect[currentIndex].display_;
			if (myDis == " ") {
				myDis = ",";
			}
			myString = myString + " " + myDis;
		}
		ofs << myString << endl;
	}
	ofs.close();
	if (ofs.is_open()) {
		throw "Could not close save file";
	}
	return 0;
}

int MagicSquareGame::deleteSave() {
	ofstream ofs("MagicSquareGame.txt");
	if (!ofs.is_open()) {
		throw "Save file could not be opened";
	}
	if (!(ofs << "NODATA" << endl)) {
		throw "Cannot write to save file";
	}
	ofs.close();
	if (ofs.is_open()) {
		throw "Could not close save file";
	}
	return 0;
}

//method to change string to int for calculating sums from display string
int MagicSquareGame::stringToInt(string a) {
	int myInt;
	stringstream mySS(a);
	mySS >> myInt;
	return myInt;
}

void MagicSquareGame::print() { cout << *this << endl; };
