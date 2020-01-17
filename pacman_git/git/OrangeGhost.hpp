#pragma once
#include "Ghost.hpp"
#include "Field.hpp"
class OrangeGhost :
	public Ghost
{
public:
	OrangeGhost();
	OrangeGhost(const int x, const int y, const int hp, const char name);
	virtual void moveToPoint(int xPacman, int yPacman, Field &field);
	~OrangeGhost();
};

