#pragma once
#include <string>
using namespace std;
enum piece_color
{
	red , 
	black,
	white,
	invalid, 
};

struct game_piece 
{
	piece_color color;
		string name;
		string display;

};

string color1(piece_color a);//step 8
piece_color color2(string a); //step 9
string lowercase(string a); //lowercase
