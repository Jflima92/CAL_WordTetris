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
int drawMenu();


int main() {

	if(!drawMenu())
	Sleep(1);
	return 0;
}


int drawMenu()
{

	cout << "Welcome to Tetris\n";
	cout << "\n1. Start Game.\n";
	cout << "6. Exit\n\n";

	int opt;

	cout << "Option: ";
	cin >> opt;
	system("cls");

	switch(opt)
	{
	case 1:
	{
		Board board;

		board.start();

		break;
	}

	case 6:
		cout << "Goodbye."<< endl;
		return 1;
		break;

	}

	return 0;

}
