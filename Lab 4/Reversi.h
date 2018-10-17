//Authors: Mike Warfield, Luke Wuri, Brian Halsell
//Header file for Reversi
#pragma once
#include "GameBase.h"

class Reversi : public GameBase {

	friend ostream& operator<< (ostream& myOut, Reversi& myGame);

public:
	Reversi(string p1, string p2);
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	virtual int save(int turns);
	virtual int deleteSave();
	void print();
	bool validMove(int index);
	
protected:
	string playerBlack;
	string playerWhite;
	int move;//1 for player 1, 2 for player 2
	bool validIndex(int index);
	void switchPlayer();
};


ostream& operator<< (ostream& myOut, Reversi& myGame);
