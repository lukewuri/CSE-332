//Authors: Brian Halsell, Luke Wuri, Mike Warfield
//Header file for game base abstract class

#pragma once
#include <vector>
#include "GamePieces.h"

using namespace std;

class GameBase {

public:
	int findLongest();
	static GameBase* thing(int a, char*b[] );
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int& a, unsigned int& b);
	virtual bool exists(unsigned int a, unsigned int b);
	virtual int turn() = 0;
	int play();
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
	


};