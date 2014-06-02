#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>

#include "piece.h"

#define LEFT_BUTTON 75;
#define RIGHT_BUTTON 77;
#define DOWN_BUTTON 80;

using std::string;
using std::ifstream;
using std::vector;


class Board // Class that stores any piece information
{

private:
	char board[10][8];     // 10 is y 8 is x | coordinates are reversed
	int score;

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
	void activePieceFall();
	void readDictionary();
	void checkWords();
	void addWords(string word);
	void start();
	void endGame();

	int activePieceLastMoveTime;
	Piece activePiece;
	Piece nextPiece;
	string matchedWord;
	vector<string> words;


};
