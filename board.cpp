#include "board.h"

Board::Board()
{
	int x,y;
	for(y = 0; y < 10; y++)
		for ( x = 0; x < 8; x++ )
			board[y][x] = ' ';

	score = 0;
}

void Board::clearScreen()
{
	for(int i = 0; i < 80; i++)
		std::cout << '\n';
}


void Board::drawBoard()
{

	int x,y;
	std::cout << "   Word Tetris          \n\n" << std::endl;

	for(y = 0; y < 10; y++)
	{
		std::cout << "|";

		for ( x = 0; x < 8; x++ )
		{
			std::cout << board[y][x] << "|";
		}

		if(y == 5)
		{
			std::cout <<  "\t|Next Piece: " << nextPiece.getPieceLetter();
		}
		std::cout << std::endl;

	}

	std::cout << "\n|Score:  " << score <<" points." << std::endl;
	std::cout << "\n|Last Matched Word:  " << matchedWord << std::endl;
}

void Board::insertNewpiece()
{
	Piece piece('A', 0, 5);

	board[piece.getX()][piece.getY()] = piece.getPieceLetter();

}
char Board::getPiecebyID(int ID)
{
	if(ID == 1)
		return 'a';

	else if(ID == 2)
		return 'b';

	else if(ID == 3)
		return 'c';

	else if(ID == 4)
		return 'd';

	else if(ID == 5)
		return 'e';

	else if(ID == 6)
		return 'f';

	else if(ID == 7)
		return 'g';

	else if(ID == 8)
		return 'h';

	else if(ID == 9)
		return 'i';

	else if(ID == 10)
		return 'j';

	else if(ID == 11)
		return 'k';

	else if(ID == 12)
		return 'l';

	else if(ID == 13)
		return 'm';

	else if(ID == 14)
		return 'n';

	else if(ID == 15)
		return 'o';

	else if(ID == 16)
		return 'p';

	else if(ID == 17)
		return 'q';

	else if(ID == 18)
		return 'r';

	else if(ID == 19)
		return 's';

	else if(ID == 20)
		return 't';

	else if(ID == 21)
		return 'u';

	else if(ID == 22)
		return 'v';

	else if(ID == 23)
		return 'x';

	else if(ID == 24)
		return 'y';

	return 'z';
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

Piece Board::generatePiece()
{
	srand (time(NULL));

	int j = rand() % 60+1;
	int aux;
	int k = rand() % 5+1;
	int c = rand() % 23+1;

	if(j > 25 )
	{
		switch(k)
		{
		case 0:
			aux = 1;
			break;

		case 1:
			aux = 5;
			break;

		case 2:
			aux = 9;
			break;

		case 3:
			aux = 15;
			break;

		case 4:
			aux = 21;
			break;
		}

		Piece piece(getPiecebyID(aux), 0, 4);
		return piece;
	}

	Piece piece(getPiecebyID(c), 0, 4);
	return piece;
}

void Board::spawnPiece()
{

	activePiece = nextPiece;

	activePieceLastMoveTime =GetTickCount();

	board[activePiece.getX()][activePiece.getY()] = activePiece.getPieceLetter();

	nextPiece = generatePiece();

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

	if(a == 27)
	{
		forceTerminate = true;
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
	if(activePiece.getY()+1  < 8)
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
		spawnPiece();

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

	system("cls");

	if(board[0][4] != ' ' && board[1][4] != ' ' )
	{
		endGame();
	}

	if(board[activePiece.getX()+1][activePiece.getY()] == ' ')
	{
		activePieceFall();
		drawBoard();
	}

	else
	{
		checkWords();
		spawnPiece();
		drawBoard();
	}


}

bool compareByLength(const string &a, const string &b)
{
	return a.size() > b.size();
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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0; c < words[l].size(); c++)
									{
										if(board[y-1][x-c] != ' ')
										{
											board[y][x-c] = board[y-1][x-c];
											board[y-1][x-c] = ' ';
										}
										else
										{
											board[y][x-c] = ' ';
										}
									}
								}

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

								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0; c < words[l].size(); c++)
									{
										if(board[y+c-1][x-c] == ' ')
										{
											board[y+c][x-c] = ' ';
										}
										else
										{
											board[y+c][x-c] = board[y+c-1][x-c];
											board[y-1][x-c] = ' ';
										}

									}
								}
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
								else if(words[l][count] != board[y+x][count])
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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0 ; c < words[l].size(); c++)
									{
										if(board[y+c-1][x] != ' '){
											board[y+c][x] = board[y+c-1][x];
											board[y+c-1][x] = ' ';
										}
										else
										{
											board[y+c][x] = ' ';
										}
									}
								}

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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0; c < words[l].size(); c++)
									{
										if(board[y+c-1][x+c] != ' ')
										{
											board[y+c][x+c] = board[y+c-1][x+c];
											board[y+c-1][x+c] = ' ';
										}
										else
										{
											board[y+c][x+c] = ' ';
										}
									}
								}

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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0; c < words[l].size(); c++)
									{
										if(board[y-1][x+c])
										{
											board[y][x+c] = board[y-1][x+c];
											board[y-1][x+c] = ' ';
										}
										else
										{
											board[y][x+c] = ' ';
										}
									}
								}

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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0; c < words[l].size(); c++)
									{
										if(board[y-c-1][x+c] != ' '){
											board[y-c][x+c] = board[y-c-1][x+c];
											board[y-c-1][x+c] = ' ';
										}
										else
										{
											board[y-c][x+c] = ' ';
										}
									}

								}

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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0 ; c < words[l].size(); c++)
									{
										if(board[y-c-words[l].size()][x] != ' '){
											board[y-c][x] = board[y-c-1][x];
											board[y-c-1][x] = ' ';
										}
										else
										{
											board[y-c][x] = ' ';
										}
									}

								}

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
								if(words[l].size() > 2)
								{
									score+=words[l].size();
									matchedWord = words[l];
									for(unsigned int c = 0; c < words[l].size(); c++)
									{
										if(board[y-c-1][x-c] != ' '){
											board[y-c][x-c] = board[y-c-1][x-c];
											board[y-c-1][x-c] = ' ';
										}
										else
										{
											board[y-c][x-c] = ' ';
										}
									}
								}

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

void Board::start()
{
	readDictionary();
	fillInitialBoard();
	nextPiece = generatePiece();
	spawnPiece();
	drawBoard();

	//	board.clearScreen();
	while(1)
	{
		if(!forceTerminate)
		{
			while(!_kbhit()){
				gameStart();
				Sleep(350);
			}
			processInput();
			drawBoard();
			system("cls");
		}
		else
			{
			system("cls");
			drawMenu();
			break;
			}
	}
}

void Board::endGame()
{
	std::cout <<"BOOOOOOOOOOM! You have lost with the score of: " << score << "!" << std::endl;
	Sleep(100);
	return;
}

void Board::drawMenu()
{

	std::cout << "Welcome to Tetris\n";
	std::cout << "\n1. Start Game.\n";
	std::cout << "6. Exit\n\n";

	int opt;

	std::cout << "Option: ";
	std::cin >> opt;
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
		std::cout << "Goodbye."<< std::endl;
		return;
		break;

	}

	return;

}
