#pragma once
#include "movableObject.hpp"
#include "Field.hpp"
class Pacman :
	public movableObject
{
private:
	bool energised_;

public:
	Pacman(const int x, const  int y, const  int hp, const  char c);
	void turn(int btnCode, Field & field);
	void move(Field & field);
	void respawn();
	char getDirection() const;
	Pacman();
	~Pacman();
};

