#include "MovableObject.h"
#include "Consts.h"

MovableObject::MovableObject()
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

MovableObject::MovableObject(const int x, const int y, const int hp, const char c)
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

char MovableObject::getDisplayName() const
{
	return displayName_;
}

int MovableObject::getX() const
{
	return posX_;
}

int MovableObject::getY() const
{
	return posY_;
}
int MovableObject::getStartingX() const
{
	return startingX_;
}
int MovableObject::getStartingY() const
{
	return startingY_;
}

void MovableObject::setStartingX(const int x)
{
	startingX_ = x;
}
void MovableObject::setStartingY(const int y)
{
	startingY_ = y;
}

void MovableObject::setX(const int x)
{
	posX_ = x;
}

void MovableObject::setY(const int y)
{
	posY_ = y;
}

void MovableObject::setHealth(const int hp)
{
	health_ = hp;
}

void MovableObject::setDisplayName(const char name)
{
	displayName_ = name;
}

char MovableObject::getDirection() const
{
	return direction_;
}

int MovableObject::getXOld() const
{
	return posXOld_;
}

int MovableObject::getYOld() const
{
	return posYOld_;
}

void MovableObject::setXOld(const int x)
{
	posXOld_ = x;
}
void MovableObject::setYOld(const int y)
{
	posYOld_ = y;
}

void MovableObject::setDirection(const char c)
{
	direction_ = c;
}

int MovableObject::getHealth() const
{
	return health_;
}


MovableObject::~MovableObject()
{
}

void MovableObject::respawn()
{
	posXOld_ = posX_ = startingX_;
	posYOld_ = posY_ = startingY_;
}

void MovableObject::makeAStep(Field field)
{
	switch (direction_) {
	case 't':
	{
		if (field.getFieldChar(getX() - 1, getY()) != '#') {
			posX_--;
		}
		break;
	}
	case 'b':
	{
		if (field.getFieldChar(getX() + 1, getY()) != '#') {
			posX_++;
		}
		break;
	}
	case 'l':
	{
		if (field.getFieldChar(getX(), getY() - 1) != '#')	{
			if(posX_ == getJumpX() && posY_ == getJumpYLeft()){
				posY_ = getJumpYRight();
			}
			else {
				posY_--;
			}
		}
		break;
	}
	case 'r':
	{
		if (field.getFieldChar(getX(), getY() + 1) != '#') {

			if (posX_ == getJumpX() && posY_ == getJumpYRight())	{
				posY_ = getJumpYLeft();
			}
			else {
				posY_++;
			}
		}
			
		break;
	}
	default:
	{
		break;
	}
	}
}
