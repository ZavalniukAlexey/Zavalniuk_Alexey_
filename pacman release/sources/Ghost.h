#pragma once
#include "MovableObject.h"
#include "Field.h"
class Ghost :
	public MovableObject
{
protected:
	bool frighten_ = false;
	bool scatter_ = true;
	bool chase_ = true;
public:
	Ghost();
	Ghost(const int x, const  int y, const  int hp, const  char c);
	void respawn();
	void moveToPoint(const int x, const int y, const Field F);
	void chooseDirection(const double top, const double bot, const double left, const double right);
	void turn(const Field field, const int xPacman, const int yPacman);
	virtual ~Ghost();
	virtual void move(const int xPacman, const int yPacman, const Field F);
};

