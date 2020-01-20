#pragma once
#include "Field.h"
class MovableObject
{

public:
	MovableObject();
	MovableObject(const int x, const int y, const int hp, const char c);
	char getDisplayName() const;
	int getX()const;
	int getY()const;
	int getStartingX()const;
	int getStartingY()const;
	void setStartingX(const int x);
	void setStartingY(const int y);
	void setX(const int x);
	void setY(const  int y);
	void setHealth(const int hp);
	void setDisplayName(const char name);
	char getDirection() const;
	int getXOld()const;
	int getYOld()const;
	void setXOld(const int x);
	void setYOld(const  int y);
	void setDirection(const char c);
	int getHealth()const;
	virtual ~MovableObject();
	virtual void respawn();
	void makeAStep(const Field field);
protected:
	int posX_;
	int posY_;
	int posXOld_;
	int posYOld_;
	int health_;
	char displayName_;
	int startingX_;
	int startingY_;
	char direction_;
};

