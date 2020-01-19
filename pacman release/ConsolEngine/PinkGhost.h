#pragma once
#include "Field.h"
#include "Ghost.h"
class PinkGhost :
	public Ghost
{
public:
	PinkGhost();
	PinkGhost(const int x, const int y, const int hp, const char name);
	void move(const int xPacman, const int yPacman, const char dirPacman, Field filed);
	~PinkGhost();
};

