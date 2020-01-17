#pragma once
#include "Ghost.hpp"
class FactoryGhost
{
private:
	Ghost fGhost;
public:
	FactoryGhost();
	FactoryGhost(Ghost gh);
	~FactoryGhost();
};

