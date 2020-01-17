#pragma once
#include "movableObject.hpp"
class FactoryMovableObject
{
protected:
	movableObject movableobject_;
public:
	FactoryMovableObject();
	FactoryMovableObject(movableObject mo);
	~FactoryMovableObject();
};

