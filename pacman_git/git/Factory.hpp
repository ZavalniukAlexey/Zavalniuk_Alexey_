#pragma once
#include "Field.hpp"
#include "Ghost.hpp"
#include "Pacman.hpp"
#include "FactoryGhost.hpp"
#include "FactoryPacman.hpp"
#include "FactoryField.hpp"

class Factory
{
private:
	Pacman fPacman;
	Ghost fRed;
	Ghost fPink;
	Ghost fBlue;
	Ghost fOrange;
	Field fField;
public:
	Factory();
	Factory(Pacman factoryPacman, Ghost factoryRed, Ghost factoryPink, Ghost factoryBlue, Ghost factoryOrange, Field factoryField);

	~Factory();
};

