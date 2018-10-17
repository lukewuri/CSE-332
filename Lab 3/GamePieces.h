//Author: Brian Halsell
//Header file for GamePiece struct

#pragma once

#ifndef GAMEPIECES_H
#define GAMEPIECES_H


using namespace std;

enum piece_color { red, black, white, brown, invalidColor, noColor };

string enumToString(piece_color myEnum);

piece_color stringToEnum(string myString);

struct Piece {
	Piece(piece_color color, string name, string display);
	piece_color color_;
	string name_;
	string display_;
};

#endif /* GAMPIECES_H */
