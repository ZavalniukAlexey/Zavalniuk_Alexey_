#pragma once
#include "Ghost.hpp"
#include "Field.hpp"
class RedGhost :
	public Ghost
{
public:
	RedGhost();
	RedGhost(const int x, const int y, const int hp, const char name);
	virtual void moveToPoint(int xPacman, int yPacman, Field &field);
	~RedGhost();
};

