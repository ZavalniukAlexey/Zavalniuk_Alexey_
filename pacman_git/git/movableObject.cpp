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
	return displayName_;
}

int movableObject::getX() const
{
	return posX_;
}

int movableObject::getY() const
{
	return posY_;
}
int movableObject::getStartingX() const
{
	return startingX_;
}
int movableObject::getStartingY() const
{
	return startingY_;
}

void movableObject::setStartingX(const int x)
{
	startingX_ = x;
}
void movableObject::setStartingY(const int y)
{
	startingY_ = y;
}

void movableObject::setX(const int x)
{
	posX_ = x;
}

void movableObject::setY(const int y)
{
	posY_ = y;
}

void movableObject::setHealth(const int hp)
{
	health_ = hp;
}

void movableObject::setDisplayName(const char name)
{
	displayName_ = name;
}

char movableObject::getDirection() const
{
	return direction_;
}

int movableObject::getXOld() const
{
	return posXOld_;
}

int movableObject::getYOld() const
{
	return posYOld_;
}

void movableObject::setXOld(const int x)
{
	posXOld_ = x;
}
void movableObject::setYOld(const int y)
{
	posYOld_ = y;
}

void movableObject::setDirection(const char c)
{
	direction_ = c;
}

int movableObject::getHealth() const
{
	return health_;
}

/*movableObject movableObject::operator=(movableObject MO)
{
	posX_ = MO.getX();
	posY_=MO.getY();
	posXOld_=MO.getXOld();
	health_=MO.getHealth();
	displayName_=MO.getDisplayName();
	startingX_=MO.getStartingX();
	startingY_=MO.getStartingY();
	direction_=MO.getDirection();
	return *this;
}*/

movableObject::~movableObject()
{
}
