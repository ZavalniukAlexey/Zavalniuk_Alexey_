#include "PinkGhost.h"


PinkGhost::PinkGhost() {
	posXOld_ = startingX_ = posX_ = 14;
	posYOld_ = startingY_ = posY_ = 14;
	health_ = 1;
	displayName_ = 'p';
	frighten_ = false;
	
	chase_ = true;
	direction_ = 'l';
}
PinkGhost::PinkGhost(const int x, const int y, const int hp, const char name) {
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

void PinkGhost::move(const int xPacman, const int yPacman, const char dirPacman, Field field) {
	switch (dirPacman) {
	case 't':
	{
		moveToPoint(xPacman - 4, yPacman, field);
		break;
	}
	case 'b':
	{
		moveToPoint(xPacman + 4, yPacman, field);
		break;
	}
	case 'l':
	{
		moveToPoint(xPacman, yPacman - 4, field);
		break;
	}
	case 'r':
	{
		moveToPoint(xPacman, yPacman + 4, field);
		break;
	}
	default:
		break;
	}
}

PinkGhost::~PinkGhost() {
}
