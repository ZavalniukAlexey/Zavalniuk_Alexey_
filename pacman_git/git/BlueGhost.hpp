#pragma once
#include "Ghost.hpp"
#include "Field.hpp"
class BlueGhost :
	public Ghost
{
public:
	BlueGhost();
	BlueGhost(const int x, const int y, const int hp, const char name);
	virtual void moveToPoint(int xPacman, int yPacman, int Red, int xRed, Field &field);
	~BlueGhost();
};

