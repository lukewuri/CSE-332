#pragma once
#include "gamepiece.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
using namespace std;
int dimension(ifstream & a, unsigned int & x, unsigned int & y); //step 11
int readingFile(ifstream &, vector<game_piece> & pos, unsigned int a, unsigned int b);