#include "movableObject.hpp"



movableObject::movableObject()
{
	posX_ = 10;
	posY_ = 10;
	posXOld_ = 10;
	posYOld_ = 10;
	health_ = 1;
	displayName_ = '%';
	startingY_ = 10;
	startingX_ = 10;
	direction_ = 't';
}
movableObject::movableObject(const int x, const int y, const int hp, const char c)
{
	posX_ = x;
	posY_ = y;
	posXOld_ = x;
	posYOld_ = y;
	health_ = hp;
	displayName_ = c;
	startingY_ = y;
	startingX_ = x;
	direction_ = 't';
}

char movableObject::getDisplayName() const
{
	return (this->displayName_);
}

int movableObject::getX() const
{
	return (this->posX_);
}

int movableObject::getY() const
{
	return (this->posY_);
}
int movableObject::getStartingX() const
{
	return (this->startingX_);
}
int movableObject::getStartingY() const
{
	return (this->startingY_);
}

void movableObject::setX(const int x)
{
	this->posX_ = x;
}

void movableObject::setY(const int y)
{
	this->posY_ = y;
}

int movableObject::getXOld() const
{
	return (this->posXOld_);
}

int movableObject::getYOld() const
{
	return (this->posYOld_);
}

void movableObject::setXOld(const int x)
{
	this->posXOld_ = x;
}
void movableObject::setYOld(const int y)
{
	this->posYOld_ = y;
}

void movableObject::setDirection(const char c)
{
	this->direction_ = c;
}

int movableObject::getHealth() const
{
	return (this->health_);
}



movableObject::~movableObject()
{
}
