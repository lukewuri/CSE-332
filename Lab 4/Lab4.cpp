// Lab3.cpp : Defines the entry point for the console application.
// Authors: Brian Halsell, Luke Wuri, Mike Warfield
#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "Lab4.h"
#include "stdafx.h"
#include "NineAlmondsGame.h"
#include "GameBase.h"
using namespace std;

int main(int argc, char * argv[])
{

	try {
		GameBase::thing(argc, argv);
		shared_ptr<GameBase> myGameP = GameBase::instance();
		int retVal = myGameP->play();
		return retVal;
	}
	catch (char const* e) {
		cout << e << endl;
		return creationError;
	}
	catch (const bad_alloc& e) {
		cout << "Memory Allocation Failed: " << e.what() << endl;
		return badMemory;
	}
	catch (...) {
		cout << "unknown error" << endl;
		return unknownError;
	}
}

//Function to print out usage message for bad command line arguments and return the bad_cl code
result_code usage_message(char * name, string correctArgs)
{
	cout << "use this format in command line: " << name << " " << correctArgs << endl;
	return bad_cl;
}