#include "BlueGhost.h"




BlueGhost::BlueGhost()
{
	posX_ = 8;
	posY_ = 21;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'B';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	
	chase_ = true;
	direction_ = 'l';
}
BlueGhost::BlueGhost(const int x, const int y, const int hp, const char name)
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

void BlueGhost::move(const int xPacman, const int yPacman, const int xRed, const int yRed, Field field)
{
	moveToPoint(2 * xRed - xPacman, 2 * yRed - yPacman, field);
}

BlueGhost::~BlueGhost()
{
}
