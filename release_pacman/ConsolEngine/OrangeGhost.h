#pragma once
#include "Ghost.h"
#include "Field.h"
class OrangeGhost :
	public Ghost
{
public:
	OrangeGhost();
	OrangeGhost(const int x, const int y, const int hp, const char name);
	virtual void move(const int xPacman, const int yPacman, Field field);
	//virtual void move(const int xPacman, const int yPacman, Field field) override;
	virtual ~OrangeGhost();
};

