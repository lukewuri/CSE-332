Lab 3
Brian Halsell --437383, Luke Wuri --445002, Mike Warfield --444341

How To Play the Game:
To play NineAlmonds: enter NineAlmonds as a command line argument. You will then be prompted for which almond to 
move and where you want to jump over another almond, as well as whether or not you want to continue the turn. 
The objective is to have a single almond left in the center.
To play MagicSquare: enter MagicSquare as a command line arguement. pick an x coordinate, a y coordinate, and a 
number to put in that coordinate. The goal is to have each row, column and diagonal add up to 15.

We first ran into errors with when trying to use a shared_ptr. We could not figure out how to get that to work, 
so instead we just manually allocated the space and cleared it ourselves. This is our manual allocation:
try {
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
We had another error with pure virtual methods that when we tried to create an object, not all of the methods were 
defined so we had an error that said abstract class instantianted. And we fixed it by defining all of the methods

Another error that we ran into was that when the game ended in a stalemate or in a success we had abort called 
and the program failed. We figured out that this was happening because we were using stoi to convert the game 
piece's display to an int. We fixed this error by creating the stringToInt function using a stringstream to 
extract the int.
We also had an error where 0 was successfully being inserted as a piece into the MagicSquareGame. We fixed 
this by checking to make sure that the number the user inputed was not zero.

Another error that we ran into was that we initialized xDim, yDim and piecesVect as members in MagicSquare
and NineAlmonds and thus when we ran NineAlmonds we didn't get proper access to these in the prompt method
since that was part of the GameBase source code. We fixed this by initialized these variables in the constructor.


One important part of our code was our decision to hold the remaining pieces in a boolean vector where the index 
corresponded to the number. This is how we kept track of which pieces had been played. We then stored the board in
another vector called piecesVect.  We did this to allow the access of whether a piece was already played in constant
time.

Some of the Edge cases we tested for: putting in invalid coordinates. Putting in quit at different times. Putting 
in numbers that are not from 0-9. Putting in pieces where there is already a piece. We tested both a stalemate and 
a victory and it worked both times. Putting in incorrect command line input.  In all of these cases, the return code
was as expected (if the program ended) and the correct usage message was printed.

Number 26 says:
Provide an overloaded public virtual (non-static) version of the prompt() method, which takes a single reference
 to an unsigned integer and has a void return type. The method should (repeatedly if necessary) prompt the user 
to type a line that is either "quit" or the value of one of the available (unplayed) pieces. If the user inputs 
"quit" the method should throw an exception (that the program's main function must catch if it is not caught 
before then). If the user inputs a string with the value of an available piece, the method should extract the
 value into the unsigned integer parameter and return.

We decided to just use return values instead of throwing exceptions because thats how our code from the NineAlmonds 
game worked and we thought it would be more modular to use similar code than having to completely rewrite it.  This 
decision was allowed by by the professor, as posted on piazza.



We used Brian's NineAlmondsGame code and divvied up the code in the following way:
Everyone was involved in refactoring the NineAlmondsGame and in figuring out how to use virtual and pure virtual 
methods. So we had numbers 1-17 divided up pretty evenly and were working together on most of them, altough Brian
wrote the ostream extractors. In the MagicSquare stuff we divided up different parts more.

Mike wrote the stalemate and done methods as well as being involved in debugging and involved in figuring out 
how to correctly use the vectors and refactoring the game_piece to have a usable int to test whether or not each 
row, col, diag added up to 15, and wrote the majority of the README

Luke wrote the prompt methods for the MagicSquareGame files and defined the pure virtual functions in the NineAlmonds
and MagicSquare cpp files. He also was the main writer/computer person for the merging of the ninealmonds game from lab
2 as an inherited game into lab 3. In general was also involved in debugging and brain storming of ideas.

Brian wrote the ostream operator, the turn method, the header file for MagicSquare Game, the constructor/member list of 
the MagicSquare Game, and the method for string to int.  Also, combined all separate parts of the MagicSquareGame class
and main debugger of it.  Generally involed in refactoring code from last lab and making necessary change.  Wrote Lab3.cpp.

