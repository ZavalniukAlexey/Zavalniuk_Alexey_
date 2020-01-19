#include "OrangeGhost.h"
#include <cmath>


OrangeGhost::OrangeGhost()
{
	posX_ = 8;
	posY_ = 22;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'O';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	chase_ = true;
	direction_ = 'l';
}
OrangeGhost::OrangeGhost(const int x, const int y, const int hp, const char name)
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

void OrangeGhost::move(const int xPacman, const int yPacman, Field field)
{
	if (sqrt((posX_ - xPacman)*(posX_ - xPacman) + (posY_ - yPacman)*(posY_ - yPacman)) <= 8)
		moveToPoint(xPacman, yPacman, field);
	else
		moveToPoint(40, 2, field);
}

OrangeGhost::~OrangeGhost()
{
}
