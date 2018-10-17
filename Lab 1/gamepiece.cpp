#include "stdafx.h"
#include "gamepiece.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;



string color1(piece_color a) {//step 8
	if (a == red) {
		return "red";
	}
	if (a == black) {
		return "black";
	}if (a == white) {
		return "white";
	}else {
		return "invalid";
	}
}

piece_color color2(string a) {//step 9
	lowercase(a);
	if (a == "red") {
		return red;
	}
	if (a == "black") {
		black;
	}
	if (a == "white") {
		return white;
	}
	else {
		return invalid;
	}
}


