//Authors: Brian Halsell, Luke Wuri, Mike Warfield

#pragma once

#ifndef NINEALMONDSGAME_H
#define NINEALMONDSGAME_H
#include "GameBase.h"

enum almond_return_vals { win = 0, quit = 2, stalemate = 3 };

class NineAlmondsGame : public GameBase{

	friend ostream& operator<< (ostream& myOut, NineAlmondsGame& myGame);

public:
	NineAlmondsGame();
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	virtual int save(int turns);
	virtual int deleteSave();
	void print();
	//int prompt(unsigned int& a, unsigned int& b);
	vector<Piece> getp();


protected:
};

ostream& operator<< (ostream& myOut, NineAlmondsGame& myGame);

#endif // !NINEALMONDSGAME_H