//============================================================================
// Name        : wtetris.cpp
// Author      : Jorge Lima
//				 Manuel Carlos
// Version     :
// Copyright   : 
// Description : World Tetris implemented in C++
//============================================================================

#include <iostream>
#include "board.h"


using namespace std;
int main() {

	Board board;
	//	cout << "Vamos testar"<< endl;
	//	board.drawBoard();
	board.fillInitialBoard();
	board.drawBoard();
	board.spawnPiece();
	board.drawBoard();

	//	board.clearScreen();

	while(1){
		board.processInput();
		board.drawBoard();
	}

	return 0;
}
