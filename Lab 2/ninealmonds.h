//File name: ninealmonds.h
//Author: Luke Wuri, lwuri@wustl.edu
//header file for ninealmonds game
//used by lab2.cpp
//sets up the game board class for ninealmonds and is instantiated in the cpp/game file.
//contains the error messages as well.
#pragma once
#define nine_almonds_header
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

class ninealmonds
{
public:
	friend ostream &operator << (ostream &out, const ninealmonds &f);
	bool done();
	bool stalemate();
	int prompt(unsigned int &a, unsigned int &b);
	int turn();
	int play();
	vector<vector<char>>B{
		{ 'x','0','1','2','3','4', '|' },
		{ '0',' ',' ',' ',' ',' ', '|' },
		{ '1',' ','A','A','A',' ', '|' },
		{ '2',' ','A','A','A',' ', '|' },
		{ '3',' ','A','A','A',' ', '|' },
		{ '4',' ',' ',' ',' ',' ', '|' },
		{ '_','_','_','_','_','_', '|' } 
	};

	/*
	   0   1   2   3  4    5    6 [row][column] -> [vertical Y][horizontal X]
	{
	{ 'x','0','1','2','3','4', ' ' },//[0][~]
	{ '0',' ',' ',' ',' ',' ', ' ' },//[1][~]
	{ '1',' ','A','A','A',' ', ' ' },//[2][~]
	{ '2',' ','A','A','A',' ', ' ' },//[3][~]
	{ '3',' ','A','A','A',' ', ' ' },//[4][~]
	{ '4',' ',' ',' ',' ',' ', ' ' }, //[5][~]
	{ ' ',' ',' ',' ',' ',' ', ' ' } };//[6][~] */

	//[y][x]

private:
	int turncount = 1;
};

enum {
	goodgame,
	goodturn,
	goodprompt,
	toolong,
	stale,
	wrongname,
	wronginputnumber,
	nocomma,
	newpiece,
	endturn,
	quit
};


ostream &operator<<(ostream &out, const ninealmonds &f);


