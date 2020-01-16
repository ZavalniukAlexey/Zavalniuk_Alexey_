#pragma once
#include "movableObject.hpp"
#include "Field.hpp"
#include "Pacman.hpp"

class Ghost :
	public movableObject
{
private:
	bool frighten_;
	bool chase_;
	bool scatter_;
public:
	double checkDistance(const int x1, const  int y1, const int x2, const  int y2);
	Ghost();
	Ghost(const int x, const  int y, const  int hp, const  char c);
	void respawn();
	void turn(const char direction, Pacman pacman, Field field);
	void moveToStop(Field &field, int steps, Pacman pacman);
	void moveToPoint(const int x, const  int y, Field &field, Pacman pacman);
	~Ghost();
};

