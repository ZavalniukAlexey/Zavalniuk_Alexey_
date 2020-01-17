#include "FactoryMovableObject.hpp"

FactoryMovableObject::FactoryMovableObject()
{
	movableobject_.setX(10);
	movableobject_.setY(10);
	movableobject_.setXOld(10);
	movableobject_.setYOld(10);
	movableobject_.setHealth(1);
	movableobject_.setDisplayName('@');
	movableobject_.setStartingX(10);
	movableobject_.setStartingY(10);
	movableobject_.setDirection(10);
}

FactoryMovableObject::FactoryMovableObject(movableObject MO)
{
	movableobject_.setX(MO.getX());
	movableobject_.setY(MO.getY());
	movableobject_.setXOld(MO.getXOld());
	movableobject_.setYOld(MO.getYOld());
	movableobject_.setHealth(MO.getHealth());
	movableobject_.setDisplayName(MO.getDisplayName());
	movableobject_.setStartingX(MO.getStartingX());
	movableobject_.setStartingY(MO.getStartingY());
	movableobject_.setDirection(MO.getDirection());
}

FactoryMovableObject::~FactoryMovableObject()
{
}

