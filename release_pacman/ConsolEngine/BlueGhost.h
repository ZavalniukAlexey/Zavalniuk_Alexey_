#pragma once
#include "Ghost.h"
class BlueGhost :
	public Ghost
{
public:
	BlueGhost();
	BlueGhost(const int x, const int y, const int hp, const char name);
	//virtual void move(const int xPacman, const int yPacman, const int xRed, const int yRed, Field field) override;
	virtual void move(const int xPacman, const int yPacman, const int xRed, const int yRed, Field field);
	virtual ~BlueGhost();
};

