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
	board.readDictionary();
	cout << board.words[1] << endl;
	board.fillInitialBoard();
	board.checkWords();
	board.drawBoard();
	board.spawnPiece();
	board.drawBoard();



	//	board.clearScreen();
	while(1)
	{

		while(!_kbhit()){

			//enquanto não é pressionada nenhuma tecla faz descer a peça
			//sempre que desce uma peça verifica que na posição a seguir não tem nenhuma peça, se tive cria cria nova peça e volta a começar
			board.gameStart();
			Sleep(500);
		}
		board.clearScreen();
		board.processInput();
		board.drawBoard();
		Sleep(150);
		board.clearScreen();
	}


	return 0;
}
