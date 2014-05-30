#include <iostream>

class Piece // Class that stores any piece information
{

private:
	char letter;
	int x;
	int y;

public:
	Piece(char let, int x, int y); // constructor
	void setPieceLetter(char let);
	void setX(int x);
	void setY(int y);
	char getPieceLetter();
	int getX();
	int getY();

};
