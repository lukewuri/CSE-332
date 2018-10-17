Name: Luke Wuri
User: lwuri
ID: 445002
Lab: Lab 2 (Nine Almonds)

To run the program, cmd input must be "lab2.exe NineAlmonds"
The name of the game MUST BE 'NineAlmonds' as it is case sensitive and space sensitive.
If more than one input or incorrect name is typed, error message plays and exits program.

To play the game, select a piece based on cartesian coordinates. For example,
if I input 2,3 I am selecting the piece with horizontal coordinate 2 and vertical 
coordinate 3. Selecting a location for the piece is a similar process, but the
location must be empty and the inbetween square must have an almond to jump over.

Players can type 'quit' at anytime. 'end' 'Y' are also other inputs for the player
to either end a turn if they just moved a piece or continue a turn if they just moved a piece.

Game ends if board is stalemated, completed, or player quits.

Problems Occurred/Solution:
-Implemented the program originally using an array and ran into assignment errors.
Work around for the problem was to use a 2D vector (vector containing vectors of char).
-Ran into minor issues with << operator? Sometimes Visual Studio said "cout is ambiguous."
Problem went away when I closed and reopened my computer, but occassionally came back.
-Out of bounds problems were an issue at first for my vector. Work around was to only allow
0 to 4 as valid inputs and making my board large enough so I would not have to worry about ever 
running out of bounds.