#pragma once
#include "Moving_object.h"
#include "Field.h"
class Pacman :
	public Moving_object
{

public:
	Pacman(int x, int y, int hp, char c);
	void Move(int btnCode, Field &f);
	void respawn();
	char getDirection();
	Pacman();
	~Pacman();
};

