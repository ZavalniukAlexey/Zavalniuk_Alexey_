#include "OrangeGhost.hpp"
#include <cmath>


OrangeGhost::OrangeGhost()
{
	posX_ = 20;
	posY_ = 6;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'O';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	scatter_ = false;
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
	scatter_ = false;
	chase_ = true;
	direction_ = 'l';
}
void OrangeGhost::moveToPoint(int xPacman, int yPacman, Field & field)
{
	double tewmp = sqrt((xPacman - posX_)*(xPacman - posX_) + (yPacman - posY_)*(yPacman - posY_));
	if (sqrt((xPacman - posX_)*(xPacman - posX_) + (yPacman - posY_)*(yPacman - posY_)) <= 8)
		moveToStop(xPacman, yPacman, field);
	else
		moveToStop(33, 2, field);
}
OrangeGhost::~OrangeGhost()
{
}
