#pragma once
#include "Field.hpp"
#include "Ghost.hpp"
class PinkGhost :
	public Ghost
{
public:
	PinkGhost();
	PinkGhost(const int x, const int y, const int hp, const char name);
	virtual void moveToPoint(int xPacman, int yPacman, char dirPacman, Field& field);
	~PinkGhost();
};

