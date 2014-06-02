#include "board.h"

Board::Board()
{
	int x,y;
	for(y = 0; y < 10; y++)
		for ( x = 0; x < 8; x++ )
			board[y][x] = ' ';
}

void Board::clearScreen()
{
	for(int i = 0; i < 60; i++)
		std::cout << '\n';
}


void Board::drawBoard()
{

	int x,y;
	for(y = 0; y < 10; y++)
	{
		std::cout << "|";

		for ( x = 0; x < 8; x++ )
		{
			std::cout << board[y][x] << "|";
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

	for(int x = 0; x < 8; x++)
	{
		int j = rand() % 23+1;
		Piece piece(getPiecebyID(j),9, x);
		board[piece.getX()][piece.getY()] = piece.getPieceLetter();
	}

}
void Board::spawnPiece()
{

	srand (time(NULL));

	int j = rand() % 23+1;
	int k = rand() % 7;

	Piece piece(getPiecebyID(j), 0, k);

	nextPiece = piece;


	activePiece = nextPiece;
	std::cout << activePiece.getX() << std::endl;
	std::cout << activePiece.getY() << std::endl;

	board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();

}

void Board::processInput()
{
	static bool leftState = false;
	static bool rightState = false;
	static bool downState = false;

	int a;
	a = _getch();
	a =  _getch();
	std::cout << a << std::endl;

	if(a == 75)
	{
		moveLeft();

	}
	if(a == 77)
	{
		if(!rightState)
		{
			moveRight();

		}
		rightState = false;
	}
	else
	{
		rightState = false;
	}


	if(a == 80)
	{
		if(!downState)
		{
			moveDown();
		}
		downState = false;
	}
	else
	{
		downState = false;
	}



}

void Board::moveLeft()
{

	board[activePiece.getX()][activePiece.getY()] = ' ';
	activePiece.setY(activePiece.getY()-1);

	board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
}

void Board::moveRight()
{
	board[activePiece.getX()][activePiece.getY()] = ' ';
	activePiece.setY(activePiece.getY()+1);
	board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
}

void Board::moveDown()
{
	board[activePiece.getX()][activePiece.getY()] = ' ';
	activePiece.setX(activePiece.getX()+1);
	board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
}



