//Authors: Brian Halsell, Luke Wuri, Mike Warfield
//Source file for Game Base abstract class

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include "Lab4.h"
#include "GameBase.h"
#include "GamePieces.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"
#include "Reversi.h"

using namespace std;

GameBase::GameBase() {
	gamePointer = nullptr;
}

shared_ptr<GameBase> GameBase::gamePointer = nullptr;

int GameBase::getx() {
	return xDim;
}
int GameBase::gety() {
	return yDim;
}
vector<Piece> GameBase::getp() {
	return piecesVect;
}
int GameBase::getlen() {
	return len;
}
int GameBase::getstrlen() {
	return strlen;
}

//method to find the longest display of the pieceVect
int GameBase::findLongest() {
	unsigned int longest = 0;
	for (int i = 0; i < len; ++i) {
		if (piecesVect[i].display_.length() > longest) {
			longest = piecesVect[i].display_.length();
		}
	}
	return longest;
}

//method to dynamically construct correct game object and return a pointer to it
void GameBase::thing(int a, char*b[]) {
	if (!(gamePointer == nullptr)) {
		throw "Game exists";
	}
	GameBase* c = 0;
	if (a == number_of_arguments) {
		if (!strcmp(b[game_name], "NineAlmonds")) {
			NineAlmondsGame *c = new NineAlmondsGame();
			gamePointer = make_shared<NineAlmondsGame>(*c);
		}
		else if (!strcmp(b[game_name], "MagicSquare")) {
			MagicSquareGame *c = new MagicSquareGame();
			gamePointer = make_shared<MagicSquareGame>(*c);
		}
		else {
			cout << "Error: Incorrect Name" <<endl;
			throw "Incorrect Name";
		}
	}
	else if (a == number_of_arguments_reversi) {
		if (!strcmp(b[game_name], "ReversiGame")) {
			Reversi *c = new Reversi(b[player1_name], b[player2_name]);
			gamePointer = make_shared<Reversi>(*c);
		}
		else {
			cout << "Error: Incorrect Name" << endl;
			throw "Incorrect Name";
		}
	}
	else {
		cout << "Error: Incorrect Number of Inputs" << endl;
		throw "Incorrect Number of Inputs";
	}
	return;
}

//method to return smart pointer to instance
shared_ptr<GameBase> GameBase::instance() {
	if (gamePointer) {
		return gamePointer;
	}
	else {
		throw "Game is null";
	}
}

//function to call turn repeatedly until game is over
int GameBase::play() {
	unsigned int counter = 0;
	int result_of_turn = 0;
	//calls turn repeatedly
	while (!done() && !stalemate() && !result_of_turn) {
		result_of_turn = turn();
		if (result_of_turn != quit) {
			counter++;
		}
	}
	cout << "Full turns used: " + to_string(counter) << endl;
	//check if game is over due to different reasons
	if (result_of_turn == quit) {
		try {
			askSave(counter);
		}
		catch(char const* e) {
			cout << e << endl;
		}
		cout << "Game quit" << endl;
		return quit;
	}
	if (stalemate()) {
		cout << "Game Stalemated" << endl;
		try {
			deleteSave();
		}
		catch (char const* e) {
			cout << e << endl;
		}
		return game_stalemate;
	}
	if (done()) {
		cout << "Game Won" << endl;
		try
		{
			deleteSave();
		}
		catch (char const* e)
		{
			cout << e << endl;
		}
		return win;
	}

	return 0;
}

//function to ask whether to save
int GameBase::askSave(int turns) {
	cout << "Save game? (Y/N)" << endl;
	//contrinue to ask until correct response has been give
	while (true) {
		string myInput;
		getline(cin, myInput);
		if (myInput == "Y") {
			return save(turns);
		}
		else if (myInput == "N") {
			return deleteSave();
		}
		else {
			cout << "Please input a valid respond" << endl;
		}
	}
}

//function to prompt user for input 
int GameBase::prompt(unsigned int& a, unsigned int& b) {
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
		int x=0;
		int y=0;
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
}

//function to check if a piece exists at a certain index in the board vector
bool GameBase::exists(unsigned int a, unsigned int b) {
	if (piecesVect[a + b * xDim].name_ != "") {
		return true;
	}
	else {
		return false;
	}
}