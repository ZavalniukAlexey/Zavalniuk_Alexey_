#pragma once
#include "Moving_object.h"
#include "Field.h"
#include "Pacman.h"

class ghost :
	public Moving_object
{
private:
	bool frighten_;
	bool chase_;
	bool scatter_;
public:
	double checkDistance(int x1, int y1, int x2, int y2);
	ghost();
	ghost(int x, int y, int hp, char c);
	void respawn();
	void turn(char direction, Pacman pacman, Field field);
	void moveToStop(Field &field, int steps, Pacman pacman);
	void moveToPoint(int x, int y, Field &field, Pacman pacman);
	~ghost();
};

