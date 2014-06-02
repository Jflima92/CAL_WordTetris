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
	for(int i = 0; i < 80; i++)
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
	activePieceLastMoveTime =GetTickCount();

	activePiece = nextPiece;

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

	if(a == 75)
	{
		if(!leftState)
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
	if(activePiece.getY()-1 >= 0)
	{
		board[activePiece.getX()][activePiece.getY()] = ' ';
		activePiece.setY(activePiece.getY()-1);

		board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
	}
}

void Board::moveRight()
{
	if(activePiece.getY()+1 >= 0)
	{
		board[activePiece.getX()][activePiece.getY()] = ' ';
		activePiece.setY(activePiece.getY()+1);
		board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
	}
}

void Board::moveDown()
{
	board[activePiece.getX()][activePiece.getY()] = ' ';
	if(board[activePiece.getX()+1][activePiece.getY()] == ' ')
	{
		activePiece.setX(activePiece.getX()+1);
		board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
	}
	else
	{
		board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();
		checkWords();
		Sleep(10);
		spawnPiece();
		clearScreen();

	}
}

void Board::activePieceFall()
{
	int max = 100;

	if(GetTickCount() >= activePieceLastMoveTime + max)
	{
		activePieceLastMoveTime = GetTickCount();
		moveDown();
	}
}

void Board::gameStart() {

	clearScreen();
	if(board[activePiece.getX()+1][activePiece.getY()] == ' ')
	{
		activePieceFall();
		drawBoard();
	}
	else
	{
		checkWords();
		Sleep(10);
		spawnPiece();
		drawBoard();
	}


}

void Board::readDictionary()
{
	string line, readString;
	ifstream file("palavras.txt");
	string palavra;
	string aux;


	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			while(line != ""){
				getline(file, line);
				palavra = line;
				//std::cout << palavra << std::endl;;
				addWords(palavra);
			}
		}
	}

	else std::cout << "Unable to open file";

	file.close();

	std::cout << "Dictionary Loaded" << std::endl;


}
void Board::addWords(string word)
{
	words.push_back(word);
}

void Board::checkWords()
{
	for(unsigned int y = 0; y < 10; y++)
	{
		for(unsigned int x = 0; x < 8; x++)
		{
			for(unsigned int l = 0; l < words.size(); l++)
			{
				if(words[l][0] == board[y][x])
				{
					int dir = 0;
					bool found = false;

					while(dir < 8 && !found)
					{

						switch(dir)
						{

						case 0:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(y-count < 0)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y-count][x])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : West" <<std::endl;
							}
							break;
						}

						case 1:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(y-count < 0 || x+count >7)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y-count][x+count])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : SouthWest" <<std::endl;
							}
							break;
						}

						case 2:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(x+count >7)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y][x+count])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : South" <<std::endl;
							}
							break;
						}

						case 3:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(y+count > 9 || x+count >7)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y+count][x+count])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : SouthEast" <<std::endl;
							}
							break;
						}

						case 4:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(y-count > 9 )
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y+count][x])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : East" <<std::endl;
							}
							break;
						}

						case 5:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(y+count > 9 || x-count < 0)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y+count][x-count])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : NorthEast" <<std::endl;
							}
							break;
						}

						case 6:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(x-count < 0)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y][x-count])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : North" <<std::endl;
							}
							break;
						}

						case 7:
						{
							unsigned int count = 1;
							bool check = true;

							while(count < words[l].length() && check)
							{
								if(y-count < 0 || x-count < 0)
								{
									dir++;
									check = false;
								}
								else if(words[l][count] != board[y-count][x-count])
								{
									dir++;
									check = false;
								}
								else
								{
									count++;
								}
							}
							if(check)
							{
								found = true;
								std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : NorthWest" <<std::endl;
							}
							break;
						}

						}
					}
				}
			}
		}
	}
}

