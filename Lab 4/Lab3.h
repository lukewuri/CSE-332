//Authors: Brian Halsell, Luke Wuri, Mike Warfield
//Header file for lab 3

#pragma once

#ifndef LAB3_H
#define LAB3_H

using namespace std;

//Enumeration corresponding to important numbers for command line arguments, such as the index for the program name and the input file
enum clArgument { prog_name = 0, game_name = 1, number_of_arguments = 2 };

//Return codes for different scenarios
enum result_code { success = 0, bad_cl = 1, game_quit = 2, game_stalemate = 3 };

//Declaration of usage message function
result_code usage_message(char * name, string correctArg);

#endif /* LAB2_H */