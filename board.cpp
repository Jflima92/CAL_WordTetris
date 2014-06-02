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
void Board::spawnPiece()
{

	srand (time(NULL));

	int j = rand() % 23+1;
	int k = rand() % 5+1;

	if(j % 2 == 0)
	{
		switch(k)
		{
		case 0:
			j = 1;
			break;

		case 1:
			j = 5;
			break;

		case 2:
			j = 9;
			break;

		case 3:
			j = 15;
			break;

		case 4:
			j = 21;
			break;

		}

	Piece piece(getPiecebyID(j), 0, 4);
	nextPiece = piece;

	}
	else
	{
		Piece piece(getPiecebyID(j), 0, 4);
		nextPiece = piece;
	}




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

	clearScreen();

	if(board[0][4] != ' ' && board[1][4] != ' ' )
	{
		endGame();
	}

	else if(board[activePiece.getX()+1][activePiece.getY()] == ' ')
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : West" <<std::endl;
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : SouthWest" <<std::endl;
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : South" <<std::endl;
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : SouthEast" <<std::endl;
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : East" <<std::endl;
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : NorthEast" <<std::endl;
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : North" <<std::endl;
									Sleep(10);
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
									std::cout <<words[l]<< "  ("<< y << ","<< x<<" )"<<"   direction : NorthWest" <<std::endl;
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
	drawBoard();
	spawnPiece();
	drawBoard();

	//	board.clearScreen();
	while(1)
	{
		std::cout << "Score: " << score <<std::endl;
		while(!_kbhit()){
			gameStart();
			Sleep(400);
		}
		clearScreen();
		processInput();
		drawBoard();
		Sleep(150);
		clearScreen();
	}
}

void Board::endGame()
{
	std::cout <<"BOOOOOOOOOOM! You have lost with the score of: " << score << "!" << std::endl;
	Sleep(100);
	return;
}
