#pragma once
#include "movableObject.hpp"
#include "Field.hpp"
class Pacman :
	public movableObject
{

public:
	Pacman(const int x, const  int y, const  int hp, const  char c);
	void move(int btnCode, Field &f);
	void respawn();
	char getDirection() const;
	Pacman();
	~Pacman();
};

