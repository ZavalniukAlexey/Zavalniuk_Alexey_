#include "RedGhost.h"



RedGhost::RedGhost()
{
	posXOld_ = startingX_ = posX_ = 14;
	posYOld_ = startingY_ = posY_ = 13;
	health_ = 1;
	displayName_ = 'r';
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
