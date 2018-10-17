//Authors: Mike Warfield, Luke Wuri, Brian Halsell
//cpp file for Reversi
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
#include "Reversi.h"

Reversi::Reversi(string p1, string p2) {
	playerBlack = p1;
	playerWhite = p2;
	xDim = 8;
	yDim = 8;

	ifstream ifs("ReversiGame.txt");
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
		for (int i = 0; i < (xDim*yDim); ++i) {
			string currPiece;
			ifs >> currPiece;
			if (currPiece == "X") {
				string name = "p1";
				string display = "X";
				Piece tempPiece(black, name, display);
				piecesVect.push_back(tempPiece);
			}
			else if (currPiece == "O") {
				string name = "p2";
				string display = "O";
				Piece tempPiece(white, name, display);
				piecesVect.push_back(tempPiece);
			}
			else {
				string name = "";
				string display = " ";
				Piece tempPiece(noColor, name, display);
				piecesVect.push_back(tempPiece);
			}
		}
		ifs >> move;

	}
	else {
		move = 1;
		for (int i = 0; i < 64; i++) {
			//only place pieces in correct spots
			if (i == 27 || i == 36) { // X
				string name = "p1";
				string display = "X";
				Piece tempPiece(black, name, display);
				piecesVect.push_back(tempPiece);
			}
			else if (i == 28 || i == 35) {
				string name = "p2";
				string display = "O";
				Piece tempPiece(white, name, display);
				piecesVect.push_back(tempPiece);
			}
			else {
				string name = "";
				string display = " ";
				Piece tempPiece(noColor, name, display);
				piecesVect.push_back(tempPiece);
			}
		}
	}

	ifs.close();

	if (ifs.is_open()) {
		throw "Could not close save file";
	}
}

void Reversi::print() {
	cout << *this << endl;
}


int Reversi::save(int turns) {
	ofstream ofs("ReversiGame.txt");
	if (!ofs.is_open()) {
		throw "Save file could not be opened";
	}
	if (!(ofs << "ReversiGame" << endl)) {
		throw "Cannot write to save file";
	}
	ofs << xDim << " " << yDim << endl;
	ofs << turns << endl;
	for (int i = 0; i < 8; ++i) {
		string myString;
		for (int j = 0; j < 8; ++j) {
			int currentIndex = i * 8 + j;
			//modify white space to , as that is easier to work with through fstreams
			string myDis = piecesVect[currentIndex].display_;
			if (myDis == " ") {
				myDis = ",";
			}
			myString = myString + " " + myDis;
		}
		ofs << myString << endl;
	}
	ofs << move << endl; // 1 for player 1's turn, 2 for player 2's turn;
	ofs.close();
	if (ofs.is_open()) {
		throw "Could not close save file";
	}

	return 0;
}

int Reversi::deleteSave() {
	ofstream ofs("ReversiGame.txt");
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


ostream& operator<< (ostream& myOut, Reversi& myGame) {
	int x = myGame.xDim;
	int y = myGame.yDim;
	for (int i = 7; i >= 0; --i) {
		string myString = to_string(i);
		myOut << myString;
		for (int j = 0; j < 8; ++j) {
			int currentIndex = i * x + j;
			myString = " " + myGame.piecesVect[currentIndex].display_;
			myOut << myString;
		}
		myOut << endl;
	}
	myOut << "X 0 1 2 3 4 5 6 7" << endl;
	return myOut;
}

bool Reversi::done() {
	bool all = true;
	unsigned countBlack = 0;
	unsigned countWhite = 0;
	for (size_t i = 0; i < piecesVect.size(); i++) {
		if (piecesVect[i].display_ == " ") {
			all = false;
		}
		if (piecesVect[i].display_ == "X") {
			countBlack++;
		}
		if (piecesVect[i].display_ == "O") {
			countWhite++;
		}
	}
	bool legal = false;

	for (size_t i = 0; i < piecesVect.size(); i++) {
		if (validMove(i)) {
			legal = true;
		}
		switchPlayer();
		if (validMove(i)) {
			legal = true;
		}
		switchPlayer();
	}
	if (all || !legal) {
		if (countBlack > countWhite) {
			cout << endl <<  playerBlack << " Won!!!!" << endl;
			deleteSave();
			return true;
		}
		if (countWhite > countBlack) {
			cout << endl << playerWhite << " Won!!!!" << endl;
			deleteSave();
			return true;
		}
		if (countBlack = countWhite) {
			return false;
		}
	}
	return false;
}


/*
returns true if there is a legal move
pass in the index to check and the display value of the player
*/
bool Reversi::validMove(int index) {// check if there is a legal move at index
									//now inplemting the check at an empty space
	if (!validIndex(index)) {
		return false;
	}
	if (piecesVect[index].display_ != " ") {
		return false;
	}
	string display, oppose;
	if (move == 1) {
		display = "X";
		oppose = "O";
	}
	else {
		display = "O";
		oppose = "X";
	}
	int dx = -1, dyStart = -8, endx = 1, endy = 8;
	if (index < 8) {//don't check to the down because its in the bottom row
		dyStart = 0;
	}
	if (index > 55) {//don't check up because its in the top row
		endy = 0;
	}
	if (index % 8 == 0) {//don't check left beceause its in the leftmost column
		dx = 0;
	}
	if (index % 8 == 7) {//don't check right because its in the rightmost column
		endx = 0;
	}

	for (dx; dx <= endx; dx++) {
		int dy = dyStart;
		for (dy; dy <= endy; dy += 8) {
			int newIndex = index + dx + dy;
			if (validIndex(newIndex) && newIndex != index) {//if its not the same coordinate and it is in the bounds of the vector
				while ((piecesVect[newIndex].display_ == oppose) && validIndex(newIndex)) {
					newIndex = newIndex + dx + dy;
					if (validIndex(newIndex)) {
						if (piecesVect[newIndex].display_ == display) {
							return true;
						}
					}
					else {
						break;
					}
				}
			}
		}
	}
	return false;

}

bool Reversi::stalemate() {
	for (size_t i = 0; i < piecesVect.size(); i++) {
		if (validMove(i)) {
			return false;
		}
	}
	switchPlayer();
	for (size_t i = 0; i < piecesVect.size(); i++) {
		if (validMove(i)) {
			return false;
		}
	}
	switchPlayer();
	if (done()) {
		return false;
	}
	deleteSave();
	return true;
}

int Reversi::turn() {
	string name;
	if (move == 1) {
		name = playerBlack;
	}
	else {
		name = playerWhite;
	}

	bool singleValidMove = false;
	for (int i = 0; i < 63; i++) {
		if (validMove(i)) {
			singleValidMove = true;
		}
	}
	if (!singleValidMove) {
		cout << "No valid move for " << name << endl;
		switchPlayer();
		return success;
	}

	int index;
	unsigned x, y;
	print();
	do {
		cout << name << "'s turn" << endl;
		if (prompt(x, y) == quit) {
			return quit;
		}
		index = (8 * y) + x;
	} while (!validMove(index));

	string own, oppose;
	if (move == 1) {
		own = "X";
		oppose = "O";
	}
	else {
		own = "O";
		oppose = "X";
	}
	piecesVect[index].display_ = own;
	for (int dx = -1; dx <= 1; dx++) { //only seems to work when checking to the left. why?
		for (int dy = -8; dy <= 8; dy += 8) {
			int newIndex = index + dx + dy;
			if (validIndex(newIndex) && newIndex != index) {//if its not the same coordinate and it is in the bounds of the vector
				while ((piecesVect[newIndex].display_ == oppose) && validIndex(newIndex)) {
					newIndex = newIndex + dx + dy;
					if (validIndex(newIndex)) {
						if (piecesVect[newIndex].display_ == own) {
							int changeindex = newIndex - dx - dy;
							if (!validIndex(changeindex)) {
								changeindex = newIndex - dx - dy;
							}

							while (piecesVect[changeindex].display_ == oppose) {
								piecesVect[changeindex].display_ = own;
								changeindex = changeindex - dx - dy;
								if (!validIndex(changeindex)) {
									break;
								}
							}

						}
					}
					else {
						break;
					}
				}
			}
		}
	}
	switchPlayer();
	return success;
}

bool Reversi::validIndex(int index) {
	if (index >= 0 && index <= 63) {
		return true;
	}
	return false;
}

void Reversi::switchPlayer() {
	if (move == 1) {
		move = 2;
	}
	else {
		move = 1;
	}
}

