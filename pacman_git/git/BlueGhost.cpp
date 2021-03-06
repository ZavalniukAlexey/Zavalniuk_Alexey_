#include "BlueGhost.hpp"



BlueGhost::BlueGhost()
{
	posX_ = 20;
	posY_ = 6;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'B';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	scatter_ = false;
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
	scatter_ = false;
	chase_ = true;
	direction_ = 'l';
}
void BlueGhost::moveToPoint(int xPacman, int yPacman, int xRed, int yRed, Field & field)
{
	moveToStop(2 * xPacman - xRed, 2 * yPacman - yRed, field);
}


BlueGhost::~BlueGhost()
{
}
