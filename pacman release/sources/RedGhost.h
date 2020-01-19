#pragma once
#include "Ghost.h"
#include "Field.h"
class RedGhost :
	public Ghost
{
public:
	RedGhost();
	RedGhost(const int x, const int y, const int hp, const char name);
	void move(const int x, const int y, const Field F);
	~RedGhost();
};

