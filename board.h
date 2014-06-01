#include <iostream>
#include <string>
#include "piece.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define LEFT_BUTTON 75;
#define RIGHT_BUTTON 77;
#define DOWN_BUTTON 80;


class Board // Class that stores any piece information
{

private:
	char board[10][8];     // 10 is y 8 is x | coordinates are reversed

public:
	Board(); // constructor
	void drawBoard();
	void gameStart();
	void clearScreen();
	void processInput();
	void insertNewpiece();
	void fillInitialBoard();
	char getPiecebyID(int ID);
	void spawnPiece();
	void moveRight();
	void moveLeft();
	void moveDown();


	Piece activePiece;
	Piece nextPiece;


};
