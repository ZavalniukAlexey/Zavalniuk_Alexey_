#pragma once
#include "MovableObject.h"
#include "Field.h"
class Pacman :
	public MovableObject
{
private:
	bool energised_;
public:
	Pacman();
	Pacman(const int x, const int y, const int hp, const char c);
	virtual void respawn();
	~Pacman();
};

