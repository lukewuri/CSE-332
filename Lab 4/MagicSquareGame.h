//Author: Brian Halsell, Luke Wuri, Mike Warfield
//Header file for Magic Square Game

#pragma once

#ifndef MAGICSQUAREGAME_H
#define MAGICSQUAREGAME_H

#include "GameBase.h"

class MagicSquareGame : public GameBase {

	friend ostream& operator<< (ostream& myOut, MagicSquareGame& myGame);

public:
	MagicSquareGame();
	virtual bool done();
	virtual bool stalemate();
	virtual int prompt(unsigned int& a);
	virtual int turn();
	virtual int save(int turns);
	virtual int deleteSave();
	void print();
	int stringToInt(string a);


protected:
	vector<bool> availPieces;
};


ostream& operator<< (ostream& myOut, MagicSquareGame& myGame);

#endif /* MAGICSQUAREGAME_H */