#include "RedGhost.h"



RedGhost::RedGhost()
{
	posX_ = 8;
	posY_ = 19;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'r';
	startingY_ = 4;
	startingX_ = 2;
	frighten_ = false;
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
	
	chase_ = true;
	direction_ = 'l';
}

void RedGhost::move(const int x, const int y, const Field F)
{
	moveToPoint(x, y, F);
}

RedGhost::~RedGhost()
{
}
