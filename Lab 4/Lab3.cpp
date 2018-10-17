// Lab3.cpp : Defines the entry point for the console application.
// Authors: Brian Halsell, Luke Wuri, Mike Warfield
#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "Lab3.h"
#include "stdafx.h"
#include "NineAlmondsGame.h"
#include "GameBase.h"
using namespace std;

int main(int argc, char * argv[])
{

	try {
		//delete dynamically allocated object on line 26
		GameBase * myGameP = GameBase::thing(argc, argv);
		if (myGameP == 0) {
			return usage_message(argv[prog_name], "GameName");
		}
		int retVal = myGameP->play();
		delete myGameP;
		return retVal;
	}
	catch (const bad_alloc& e) {
		cout << "Memory Allocation Failed: " << e.what() << endl;
	}
}

//Function to print out usage message for bad command line arguments and return the bad_cl code
result_code usage_message(char * name, string correctArgs)
{
	cout << "use this format in command line: " << name << " " << correctArgs << endl;
	return bad_cl;
}