//File name: lab2.cpp
//Author: Luke Wuri, lwuri@wustl.edu
//Contains the methods associated with ninealmonds game
//To run, the game name parameter MUST be 'NineAlmonds'

#include "stdafx.h"
#include "ninealmonds.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

//4
//3
//2
//1
//01234

ostream &operator << (ostream &out, const ninealmonds &f) {
	for (int w = 6; w >= 0; w--) {
		for (int z = 0; z <= 6; z++) {
			out << f.B[w][z] << ' ';
		}
		out << endl << endl;
	}
	return out;
}

bool ninealmonds::done() {
	int emptyspace = 0;
	for (int x = 1; x <= 6; x++) {
		for (int y = 1; y <= 6; y++) {
			if (B[x][y] == ' ') {
				emptyspace++;
			}
		}
	}
	if (emptyspace == 24 && B[3][3] == 'A') {
		return true;
	}
	else
		return false;
}

bool ninealmonds::stalemate() {
	if (done() == true) {
		return false;
	}
	for (int x = 1; x < 6; x++) {
		for (int y = 1; y < 6; y++) {

			if (B[x][y] == 'A') {
				if (B[x - 1][y] == 'A') { //left of square
					return false;
				}
				if (B[x + 1][y] == 'A') {//right of square
					return false;
				}
				if (B[x][y + 1] == 'A') {//top of square
					return false;
				}
				if (B[x][y - 1] == 'A') {//bottom of square
					return false;
				}
				if (B[x - 1][y + 1] == 'A') {//upper left of square
					return false;
				}
				if (B[x + 1][y + 1] == 'A') {//upper right of square
					return false;
				}
				if (B[x - 1][y - 1] == 'A') {//lower left of square
					return false;
				}
				if (B[x + 1][y - 1] == 'A') {//lower right of square
					return false;
				}
			}
		}
	}
	return true;
}

int ninealmonds::prompt(unsigned int &a, unsigned int &b) {
	cout << "Type 'quit' to quit or enter a coordinate 'horizontal,vertical' to select a square" << endl;
	cout << "Valid coordinates are between 0 and 4, inclusive" << endl;
	string thing;
	getline(cin, thing);
	if (thing == "quit") {
		cout << "Good-bye!" << endl;
		return quit;
	}
	if (thing == "end") {
		cout << "Turn ended!" << endl;
		return endturn;
	}
	if (thing == "new piece") {
		cout << "Old piece deselected. Select a newpiece now" << endl;
		return newpiece;
	}
	if (thing.length() != 3) {
		cout << "Input size incorrect; must be exactly 3 char units" << endl;
		return wronginputnumber;
	}
	if (thing[1] != ',') {
		cout << "Check comma placement for coordinates! " << endl;
		return nocomma;
	}
	if ((thing[0] == '0') || (thing[0] == '1') || (thing[0] == '2') || (thing[0] == '3') || (thing[0] == '4')) {
		if (thing[1] == ',') {
			if ((thing[2] == '0') || (thing[2] == '1') || (thing[2] == '2') || (thing[2] == '3') || (thing[2] == '4')) {
				a = thing[0] - 48;
				b = thing[2] - 48;
				return goodprompt;
			}
		}
	}
	cout << "Make sure the input contains only one comma and coordinates are between 0 and 4" << endl;
	cout << "Proper format example: '0,4'   '3,0'   '2,3' " << endl <<endl;
	return(prompt(a, b));
	return goodprompt;

}

//processes the move using prompt to take in inputs
int ninealmonds::turn() {
	cout << "Turn count is: " << turncount << endl;
	//a,b is current location; c,d is target location; 
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned int c = 0;
	unsigned int d = 0;

	unsigned int prompt2 = 25;
	unsigned int prompt1 = 25;
	string yesorno;

	bool properturn = false;
	while (properturn == false) {
		label3:
		cout << *this;
		cout << "Enter the coordinates of the PIECE you want to move" << endl;
		prompt1 = prompt(a, b);
		if (prompt1 == quit) {
			cout << "Good quit" << endl;
			return quit;
		}
		if (prompt1 == newpiece) {
			return turn();
		}
		if (prompt1 == wronginputnumber) {
			return turn();
		}
		if (prompt1 == nocomma) {
			return turn();
		}
		if (prompt1 != quit) {
			if (B[b + 1][a + 1] == 'A') {
				label2:
				cout <<endl<< "Enter the LOCATION you want to jump to. Type 'new piece' to select a new piece instead. Current piece selected: " << a << "," << b << endl;
				cout << *this;
				prompt2 = prompt(c, d);
				if (prompt2 == newpiece) {
					return turn();
				}
				if (prompt2 == quit) {
					cout << "Good quit" << endl;
					return quit;
				}
				if (prompt2 == wronginputnumber) {
					cout << "Wrong input number for LOCATION. Please try again" << endl;
					goto label2;
				}
				if (prompt2 == nocomma) {
					cout << "Wrong comma placement for LOCATION. Please try again" << endl;
					goto label2;
				}
				//below if statement requires the targeted location be blank, the "jumped square" have an almond, and the targeted location must be valid (difference of 2)
				if ((B[(b + d) / 2 + 1][(a + c) / 2 + 1] == 'A' && (B[d + 1][c + 1] == ' ')) && ((((b > d) ? b - d : d - b) == 2) || ((a > c) ? a - c : c - a) == 2)) {
					B[b + 1][a + 1] = ' ';
					B[d + 1][c + 1] = 'A';
					B[(b + d) / 2 + 1][(a + c) / 2 + 1] = ' ';
					cout << properturn;
					properturn = true;
					cout << properturn;
				}
				else {
					cout << "-----Invalid coordinate of piece or location. Please select a proper location to land on.------" << endl << endl;
					goto label2;
				}
			}
			else {
				cout << "-----Location contains no Almond. Please select a proper location to land on.-----" << endl << endl;
				goto label3;
			}

		}
		else{
			cout << "Good quit" << endl;
			return quit;
		
		}
	}
label:
	cout << *this << endl;
	cout << a << "," << b << " to " << (a + c) / 2  << "," << (b + d) / 2  << " to " << c << "," << d << endl << endl;
	cout << "Continue this turn? Input 'Y' to continue or anything else to end turn for this piece." << endl;
	cout << "Type 'quit' to quit." << endl;
	getline(cin, yesorno);
	if (yesorno[0] == 'Y') {
		a = c;
		b = d;
		label4:
		cout << "Where to next? Type 'quit' to quit, 'end' to end turn. Currently selected almond: " << a << "," << b << endl;
		cout << *this << endl;
		int cd = prompt(c, d);
		if (cd== quit) {
			return quit;
		}
		if (cd == endturn) {
			turncount++;
			return goodturn;
		}
		if ((B[(b + d) / 2 + 1][(a + c) / 2 + 1] == 'A' && (B[d + 1][c + 1] == ' ')) && ((((b > d) ? b - d : d - b) == 2) || ((a > c) ? a - c : c - a) == 2)) {
			B[b + 1][a + 1] = ' ';
			B[d + 1][c + 1] = 'A';
			B[(b + d) / 2 + 1][(a + c) / 2 + 1] = ' ';
			goto label;
			return goodturn;
		}
		else {
			cout << "Invalid location. Please try again!" << endl;
			goto label4;
		}
	
	}
	if (yesorno == "quit") {
		cout << "Thanks for playing!";
		return quit;
	}
	turncount++;
	return goodturn;
}



int ninealmonds::play() {
	cout << *this;
	while (0==0 ) {
	if (done() == true) {
		cout << "Victory in: " << turncount << " turns.  Congratulations!!!!";
		return goodgame;
	}
	if (stalemate() == true) {
		cout << "Stalemate in: " << turncount << " turns.";
		return stale;
	}
	if (turn() == quit) {
		cout << "Defeat in: " << turncount << " turns.";	
		return quit;	
	}
	
}	
	return goodgame;
	
}

int main(int argc, char * argv[])
{
	int arguments = 2;
	if (argc != arguments) {
		cout << "Please check the number of arguments you typed in..." << endl << endl;
		return wronginputnumber;
	}
	string name = argv[1];
	if (name != "NineAlmonds"){
		cout << "Please check the name of the game you typed in..." << endl << endl;
		return wrongname;
	}
	ninealmonds object;
	return object.play();
}

