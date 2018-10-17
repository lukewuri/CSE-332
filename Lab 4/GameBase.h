//Authors: Brian Halsell, Luke Wuri, Mike Warfield
//Header file for game base abstract class

#pragma once
#include <memory>
#include "GamePieces.h"

using namespace std;

class GameBase {

public:
	GameBase();
	int findLongest();
	static void thing(int a, char*b[] );
	static shared_ptr<GameBase> instance();
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int& a, unsigned int& b);
	virtual bool exists(unsigned int a, unsigned int b);
	virtual int turn() = 0;
	int play();
	int askSave(int turns);
	virtual int save(int turns) = 0;
	virtual int deleteSave() = 0;
	int getx();
	int gety();
	vector<Piece> getp();
	int getlen();
	int getstrlen();
private:
protected:
	int xDim;
	int yDim;
	vector<Piece> piecesVect;
	int len;
	int strlen;
	static shared_ptr<GameBase> gamePointer;
};