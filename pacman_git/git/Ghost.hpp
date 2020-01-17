#pragma once
#include "movableObject.hpp"
#include "Field.hpp"

class Ghost :
	public movableObject
{
protected:
	bool frighten_;
	bool chase_;
	bool scatter_;
public:
	double checkDistance(const int x1, const  int y1, const int x2, const  int y2);
	Ghost();
	Ghost(const int x, const  int y, const  int hp, const  char c);
	void respawn();


	void changeDirection(const int x, const int y, Field field);
	void moveToStop(const int xPacman, const int yPacman, Field & field);
	virtual void moveToPoint(const int xPacman, const int yPAcman, Field &field);


	

	virtual ~Ghost();
};

