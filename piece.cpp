#include "piece.h"

Piece::Piece(char let, int x, int y)
{
	this->letter = let;
	this->x = x;
	this->y = y;
}

void Piece::setPieceLetter(char let)
{
	this->letter = let;
}
char Piece::getPieceLetter()
{
	return letter;
}


void Piece::setX(int x)
{
	this->x = x;
}

int Piece::getX()
{
	return x;
}

void Piece::setY(int y)
{
	this->y = y;
}
int Piece::getY()
{
	return y;
}



