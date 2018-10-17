
//Author: Brian Halsell brianhalsell@wustl.edu
//Source file for Nine Almonds Game

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Lab4.h"
#include "GamePieces.h"
#include "NineAlmondsGame.h"
using namespace std;

NineAlmondsGame::NineAlmondsGame()
	{
	xDim = 5;
	yDim = 5;
	//check save  file
	ifstream ifs("NineAlmondsGame.txt");
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
				ifs >> currPiece;
				if (currPiece == "A") {
					string name = "almond";
					string display = "A";
					Piece tempPiece(brown, name, display);
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
	}
	else {
		for (int i = 0; i < xDim * yDim; ++i) {
			//only place pieces in correct spots
			if ((i % 5 != 0) && (i % 5 != 4) && (i > 4) && (i < 21)) {
				string name = "almond";
				string display = "A";
				Piece tempPiece(brown, name, display);
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
	if (ifs.is_open()){
		throw "Could not close save file";
	}
}

vector<Piece> NineAlmondsGame::getp() {
	return piecesVect;
}


//function which returns true if game is won and false otherwise
bool NineAlmondsGame::done() {
	bool isDone = true;
	int midIndex = (xDim*yDim - 1) / 2;
	//check if center piece is almond
	if (piecesVect[midIndex].name_ != "almond") {
		isDone = false;
	}
	//check that all other squares are empty
	for (int i = 0; i < midIndex; ++i) {
		if (piecesVect[i].name_ != "") {
			isDone = false;
		}
	}
	for (int i = midIndex + 1; i < xDim * yDim; ++i) {
		if (piecesVect[i].name_ != "") {
			isDone = false;
		}
	}
	if (isDone) {
		try {
			deleteSave();
		}
		catch (char const* e) {
			cout << e << endl;
		}
	}
	return isDone;
}

//function that returns true if there are no possible moves and false otherwise
bool NineAlmondsGame::stalemate() {
	bool isStalemate = true;
	if (done()) {
		return false;
	}
	for (int i = 0; i < xDim * yDim; ++i) {
		//if pieces exists at location, iterate over all neighbors
		if (piecesVect[i].name_ == "almond") {
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					int neighborIndex = i + dx + xDim * dy;
					int jumpPosIndex = i + 2 * dx + 2 * xDim * dy;
					//check that the final position after jump is within game board bounds
					if (jumpPosIndex >= 0 && jumpPosIndex < xDim * yDim) {
						if (piecesVect[neighborIndex].name_ == "almond" && piecesVect[jumpPosIndex].name_ == "") {
							isStalemate = false;
						}
					}
				}
			}
		}
	}
	if (isStalemate) {
		try {
			deleteSave();
		}
		catch (char const* e) {
			cout << e << endl;
		}
	}
	return isStalemate;
}

/*
//function to prompt user for input 
int NineAlmondsGame::prompt(unsigned int& a, unsigned int& b) {
	bool validCoord = false;
	//Continue to ask for correct coordinates until a correct pair is given
	while (!validCoord) {
		cout << "Input valid coordinate in form 0,0 or type quit to quit" << endl;
		string myInput;
		getline(cin, myInput);
		if (myInput == "quit") {
			return quit;
		}
		//extract each coordinate from input
		string modifiedStr;
		replace(myInput.begin(), myInput.end(), ',', ' ');
		istringstream myISStream(myInput);
		int x;
		int y;
		if (myISStream >> x && myISStream >> y) {
			if (x >= 0 && x < xDim && y >= 0 && y < yDim) {
				a = x;
				b = y;
				validCoord = true;
			}
		}
		if (!validCoord) {
			cout << "Invalid input given." << endl;
		}
	}
	return 0;
} */

//function to implement one turn of the game
int NineAlmondsGame::turn() {
	string turnMoves;
	bool validMove = false;
	unsigned int startX;
	unsigned int startY;
	unsigned int endX;
	unsigned int endY;
	print();
	//continue to ask more moves until a valid move is given
	while (!validMove) {
		cout << "Give the coordinate of the piece to move" << endl;
		if (prompt(startX, startY) == quit) {
			return quit;
		}
		cout << "Give the coordinate of the destination of the move" << endl;
		if (prompt(endX, endY) == quit) {
			return quit;
		}
		//check that move is correct distance
		int dx = (int)endX - (int)startX;
		int dy = (int)endY - (int)startY;
		if ((abs(dx) == 2 && dy == 0) || (abs(dy) == 2 && dx == 0) || (abs(dx) == 2 && abs(dy) == 2)) {
			if (exists(startX, startY)) {
				unsigned int neighborX = startX + dx / 2;
				unsigned int neighborY = startY + dy / 2;
				if (exists(neighborX, neighborY)) {
					if (!exists(endX, endY)) {
						//move piece and removed jumped piece
						unsigned int startIndex = startX + startY * xDim;
						unsigned int endIndex = endX + endY * xDim;
						unsigned int jumpedIndex = neighborX + neighborY * xDim;
						string name = "";
						string display = " ";
						Piece emptyTile(noColor, name, display);
						Piece emptyTile2(noColor, name, display);
						piecesVect[startIndex] = emptyTile;
						piecesVect[jumpedIndex] = emptyTile2;
						name = "almond";
						display = 'A';
						Piece newPosition(brown, name, display);
						piecesVect[endIndex] = newPosition;
						validMove = true;
						//update string containing turn moves
						turnMoves = to_string(startX) + "," + to_string(startY);
						string newMoves = " to " + to_string(endX) + ',' + to_string(endY);
						turnMoves = turnMoves + newMoves;
					}
				}
			}
		}
		if (!validMove) {
			cout << "Invalid Move" << endl;
		}
	}
	//ask for additional moves in same turn
	bool newTurn = false;
	while (!newTurn) {
		bool answered = false;
		string tempString;
		string tempInput;
		//continue to ask player if they want to continue turn until they enter Y or N
		while (!answered) {
			cout << *this << endl;
			if (stalemate()) {
				return game_stalemate;
			}
			if (done()) {
				return win;
			}
			cout << turnMoves << endl;
			cout << "Move again this turn (Y for Yes, N for No)" << endl;
			getline(cin, tempString);
			istringstream tempISStream(tempString);
			tempISStream >> tempInput;
			if (tempInput == "Y") {
				answered = true;
			}
			else if (tempInput == "N") {
				newTurn = true;
				answered = true;
			}
			else {
				cout << "Invalid Response" << endl;
			}
		}
		//if turn is being continued, then ask for new destination coordinates
		if (!newTurn) {
			unsigned int a;
			unsigned int b;
			bool validMove = false;

			cout << "Give the coordinate of the destination of the move" << endl;
			if (prompt(a, b) == quit) {
				return quit;
			}
			startX = endX;
			startY = endY;
			endX = a;
			endY = b;
			//check that move is correct distance
			int dx = (int)endX - (int)startX;
			int dy = (int)endY - (int)startY;
			if ((abs(dx) == 2 && dy == 0) || (abs(dy) == 2 && dx == 0) || (abs(dx) == 2 && abs(dy) == 2)) {
				if (exists(startX, startY)) {
					unsigned int neighborX = startX + dx / 2;
					unsigned int neighborY = startY + dy / 2;
					if (exists(neighborX, neighborY)) {
						if (!exists(endX, endY)) {
							//move piece and removed jumped piece
							unsigned int startIndex = startX + startY * xDim;
							unsigned int endIndex = endX + endY * xDim;
							unsigned int jumpedIndex = neighborX + neighborY * xDim;
							string name = "";
							string display = " ";
							Piece emptyTile(noColor, name, display);
							Piece emptyTile2(noColor, name, display);
							piecesVect[startIndex] = emptyTile;
							piecesVect[jumpedIndex] = emptyTile2;
							name = "almond";
							display = 'A';
							Piece newPosition(brown, name, display);
							piecesVect[endIndex] = newPosition;
							validMove = true;
							//update string containing turn moves
							string newMoves = " to " + to_string(endX) + ',' + to_string(endY);
							turnMoves = turnMoves + newMoves;
						}

					}

				}
				if (!validMove) {
					cout << "Invalid Input" << endl;
					answered = false;
				}
			}
		}
	}


	return 0;
}

//method to save game state
int NineAlmondsGame::save(int turns) {
	ofstream ofs("NineAlmondsGame.txt");
	if (!ofs.is_open()) {
		throw "Save file could not be opened";
	}
	if (!(ofs << "NineAlmondsGame" << endl)) {
		throw "Cannot write to save file";
	}
	ofs << xDim << " " << yDim << endl;
	ofs << turns << endl;
	for (int i = 0; i < 5; ++i) {
		string myString;
		for (int j = 0; j < 5; ++j) {
			int currentIndex = i * 5 + j;
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

int NineAlmondsGame::deleteSave() {
	ofstream ofs("NineAlmondsGame.txt");
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

//insertion operator to print game boards
ostream& operator<< (ostream& myOut, NineAlmondsGame& myGame) {
	int x = myGame.xDim;
	int y = myGame.yDim;
	for (int i = 4; i >= 0; --i) {
		string myString = to_string(i);
		for (int j = 0; j < 5; ++j) {
			int currentIndex = i * x + j;
			myString = myString + " " + myGame.piecesVect[currentIndex].display_;
		}
		myOut << myString << endl;
	}
	myOut << "X 0 1 2 3 4" << endl;
	return myOut;
}

void NineAlmondsGame::print() { cout << *this << endl; };