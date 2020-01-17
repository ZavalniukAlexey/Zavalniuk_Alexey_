#include "RedGhost.hpp"



RedGhost::RedGhost()
{
	posX_ = 20;
	posY_ = 6;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'r';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	scatter_ = false;
	chase_ = true;
	direction_ = 'l';
}
RedGhost::RedGhost(const int x, const int y, const int hp, const char name)
{
	posX_ = x;
	posY_ = y;
	posXOld_ = x;
	posYOld_ = y;
	health_ = hp;
	displayName_ = name;
	startingY_ = y;
	startingX_ = x;
	frighten_ = false;
	scatter_ = false;
	chase_ = true;
	direction_ = 'l';
}

void RedGhost::moveToPoint(int xPacman, int yPacman, Field & field)
{
	moveToStop(xPacman, yPacman, field);
}


RedGhost::~RedGhost()
{
}
