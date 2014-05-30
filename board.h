#include <iostream>
#include <string>
#include "piece.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


class Board // Class that stores any piece information
{

private:
	char board[10][8];     // 10 is y 8 is x | coordinates are reversed

public:
	Board(); // constructor
	void drawBoard();
	void gameStart();
	void clearScreen();
	void insertNewpiece();
	void fillInitialBoard();
	char getPiecebyID(int ID);
	void moveRight();
	void moveLeft();
	void moveDown();


};
