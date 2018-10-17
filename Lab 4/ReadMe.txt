Lab 4
Authors: Brian Halsell, Mike Warfield, Luke Wuri 
NOTE: We were given an extension until Sunday by Professor Shidal
NOTE: Be sure to include "NODATA" save files we have supplied into the debug folder.  In earlier tries the program would automatically
create these files if they did not exist, but we ran into situations where the program did not do that later on.

NineAlmondsGame and MagicSquareGame work the same as in Lab 3, but with the added ability to save games.  When a user quits in the
middle of a game, the game asks the user to input Y or N to choose whether to save.  If the user chooses yes, the program saves data
into a text file in a format specific to each game (formats described below).  If the user chooses no, the program writes "NODATA"
into the text file.  When the program starts and a game is chosen, the program looks at the save file to see if there is data.
If the text file has "NODATA" written, the program constructs a game with parameters corresponding to a new game of the specified type.
If the text file does not, the program uses the data in the save file to construct a game.  In the save files, empty spaces are represented
by "," instead of " ", as this allows for simpler reading in of data as white space at the end of a row will not be ignored for extraction.

When a game finishes or stalemates, "NODATA" is written to the save file.

NineAlmondsGame save file format:

NineAlmondsGame
xDim yDim
turns
Game Board State(row by row)

Example:
NineAlmondsGame
5 5
0
 , , , , ,
 , A A A ,
 , A A A ,
 , A A A ,
 , , , , ,


 MagicSquareGame save file format:

 MagicSquareGame
 xDim yDim
 turns
 Game Board State(row by row)

Example:
MagicSquareGame
3 3
1
 , , ,
 , 1 ,
 , , ,

 (Note: available pieces are not saved, as which pieces are available can be found from reading in which pieces have been used)

 Errors encountered:
 A few out of bounds index errors while modifying save methods, fixed easily with adjusting for loop conditions

 Tests: Input all of the usual badly formed command line arguments and received to correct corresponding error messages/return codes.
 Both finished and stalemated games to make sure saved data was correctly erased.
 Quit and did not save, confirmed that game was not saved to text file.
 Saved various games and checked that restarting game produced correct board.


  ReversiGame save file format:

 ReversiGame
 xDim yDim
 turns
 Game Board State(row by row)
 player's turn

Example:
ReversiGame
3 3
1
 , , , , ,
 , X O , , 
 , O X , ,
 , , , , ,
 , , , , ,
1


 Errors encountered:
 A few out of bounds index errors while modifying save methods, fixed easily with adjusting for loop conditions

 Tests: Input all of the usual badly formed command line arguments and received to correct corresponding error messages/return codes.
 Both finished and stalemated games to make sure saved data was correctly erased.
 Quit and did not save, confirmed that game was not saved to text file.
 Saved various games and checked that restarting game produced correct board.



 ReversiGame:
 To run Reversi type in the following as a command line arguments: lab4.exe ReversiGame Name1 Name2
 We run the Reversi Game by first testing if the coordinate the user enters is a valid coordinate for a move.
 If it is we then go back and change everything in the path of the move. After each turn, we make sure to check if 
 it is stalemate and done and switch the players turn. 

 Tests: We ran through several different iterations of the game that came to successful conclusions with pieces being flipped
 in the approprate manner. We also tested cases where the save file was modified so that it started in a done or stalemated
 state and it was handled correctly. We also tested cases with bad command line arguments and these were all handled
 as expected.

 Errors Encountered: We ran into errors with vector subscripts running out of range. This was fixed by adding a couple of else
 break out of the wild loop statements, because the new index was out of bounds and it would go check that index in validMove
 in the while loop conditional. Another error was with the for loops in validMove. WE were forgetting to reset the second for 
 loop each time, so it would be 8 for every iteration except the first, so that was not working.

 Copy/Move decisions:
 Note: Unused constructors and operators were not strictly forbidden (just not defined), as this was unnecessary given that there is no option to use
 these given our program, so they cannot be abused.  In addition, this allows later versions of the game to use them if necessary.

 NineAlmondsGame:
	copy constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	move constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	copy-assignment operator - Not defined, as we never define multiple games in one run of the program, so copy-assigning is not necessary
	move-assignment operator - Used default move-assignment operator, as move-assignment is done in the standard fashion in our program and only 
				   done at the start of the program (ensured default move-assignment operator through not defining one)
	destructor - Used default destructors as destruction of heap objects was standard and controlled by shared_ptrs in our program

 MagicSquareGame:
	copy constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	move constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	copy-assignment operator - Not defined, as we never define multiple games in one run of the program, so copy-assigning is not necessary
	move-assignment operator - Used default move-assignment operator, as move-assignment is done in the standard fashion in our program and only 
				   done at the start of the program (ensured default move-assignment operator through not defining one)
	destructor - Used default destructors as destruction of heap objects was standard and controlled by shared_ptrs in our program

 ReversiGame:
	copy constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	move constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	copy-assignment operator - Not defined, as we never define multiple games in one run of the program, so copy-assigning is not necessary
	move-assignment operator - Used default move-assignment operator, as move-assignment is done in the standard fashion in our program and only 
				   done at the start of the program (ensured default move-assignment operator through not defining one)
	destructor - Used default destructors as destruction of heap objects was standard and controlled by shared_ptrs in our program

 GameBase:
	copy constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	move constructor - Not defined, as we only construct new objects of this class in our program through the one constructor that we have defined
	copy-assignment operator - Not defined, as we never define multiple games in one run of the program, so copy-assigning is not necessary
	move-assignment operator - Used default move-assignment operator, as move-assignment is done in the standard fashion in our program and only 
				   done at the start of the program (ensured default move-assignment operator through not defining one)
	destructor - Used default destructors as destruction of heap objects was standard and controlled by shared_ptrs in our program



 What Each Person Did:
 Mike: Wrote much of the code for Reversi, including most of turn and validMove. Also involved in debugging.

 Luke: Involved in debugging throughout the Reversi class, and helped write the methods. Also provided food and drinks

 Brian: Updated NineAlmondsGame, MagicSquareGame, and GameBase for this lab.  Added saving functionality for games.  Wrote ReadMe.txt for corresponding 
 sections (old game saving descriptions) and for copy/move decisions. Involved in debugging.