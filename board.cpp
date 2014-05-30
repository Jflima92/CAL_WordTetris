#include "board.h"


Board::Board()
{
	int x,y;
	for(x = 0; x < 10; x++)
		for ( y = 0; y < 8; y++ )
			board[x][y] = ' ';
}

void Board::clearScreen()
{
	for(int i = 0; i < 60; i++)
		std::cout << '\n';
}


void Board::drawBoard()
{

	int x,y;
	for(x = 0; x < 10; x++)
	{
		std::cout << "|";

		for ( y = 0; y < 8; y++ )
		{
			std::cout << board[x][y] << "|";
		}

		std::cout << std::endl;
	}
}


void Board::gameStart() {

	srand (time(NULL));

	int j = rand() % 23+1;
	int k = rand() % 7;

	Piece piece(getPiecebyID(j), 0, k);


	board[piece.getX()][piece.getY()] = piece.getPieceLetter();
}


void Board::insertNewpiece()
{
	Piece piece('A', 0, 5);

	board[piece.getX()][piece.getY()] = piece.getPieceLetter();

}
char Board::getPiecebyID(int ID)
{
	if(ID == 1)
		return 'A';

	else if(ID == 2)
		return 'B';

	else if(ID == 3)
		return 'C';

	else if(ID == 4)
		return 'D';

	else if(ID == 5)
		return 'E';

	else if(ID == 6)
		return 'F';

	else if(ID == 7)
		return 'G';

	else if(ID == 8)
		return 'H';

	else if(ID == 9)
		return 'I';

	else if(ID == 10)
		return 'J';

	else if(ID == 11)
		return 'K';

	else if(ID == 12)
		return 'L';

	else if(ID == 13)
		return 'M';

	else if(ID == 14)
		return 'N';

	else if(ID == 15)
		return 'O';

	else if(ID == 16)
		return 'P';

	else if(ID == 17)
		return 'Q';

	else if(ID == 18)
		return 'R';

	else if(ID == 19)
		return 'S';

	else if(ID == 20)
		return 'T';

	else if(ID == 21)
		return 'U';

	else if(ID == 22)
		return 'V';

	else if(ID == 23)
		return 'X';

	else if(ID == 24)
		return 'Y';

	return 'Z';
}

void Board::fillInitialBoard()
{
	srand (time(NULL));

	for(int i = 1; i <= 8; i++)
	{
		int j = rand() % 23+1;
		Piece piece(getPiecebyID(j),9, i);
		board[piece.getX()][piece.getY()-1] = piece.getPieceLetter();
	}

}





