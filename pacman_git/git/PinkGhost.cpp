#include "PinkGhost.hpp"



PinkGhost::PinkGhost()
{
	posX_ = 20;
	posY_ = 6;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'p';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	scatter_ = false;
	chase_ = true;
	direction_ = 'l';
}
PinkGhost::PinkGhost(const int x, const int y, const int hp, const char name)
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

void PinkGhost::moveToPoint(int xPacman, int yPacman, char dirPacman, Field & field)
{
	switch (dirPacman)
	{
	case 't':
	{
		moveToStop(xPacman, yPacman - 4, field);
		break;
	}
	case 'b':
	{
		moveToStop(xPacman, yPacman + 4, field);
		break;
	}
	case 'l':
	{
		moveToStop(xPacman-4, yPacman - 4, field);
		break;
	}
	case 'r':
	{
		moveToStop(xPacman+4, yPacman, field);
		break;
	}
	}
}


PinkGhost::~PinkGhost()
{
}
