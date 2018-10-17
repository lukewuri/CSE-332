#pragma once
//lab1common.h
//name:Luke Wuri
//e-mail: lwuri@wustl.edu//ID:445002
#include <vector>
#include "gamepiece.h"
using namespace std;
enum Indices {
	ProgramNameIndex,
	InputFileNameIndex,
	NumOfArguments
};

enum ErrorValues {
	Success,
	CannotOpenFile,
	CannotExtractDimension,
	Not5Extractions,
	InvalidExtract,
	GetLineFail
};

int print(const vector<game_piece> & a, unsigned int x, unsigned int y);