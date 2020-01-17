#include "Factory.hpp"




Factory::Factory()
{
}

Factory::Factory(Pacman factoryPacman, Ghost factoryRed, Ghost factoryPink, Ghost factoryBlue, Ghost factoryOrange, Field factoryField)
{
	Pacman fPacman(factoryPacman);
	Ghost fRed(factoryRed);
	Ghost fPink(factoryPink);
	Ghost fBlue(factoryBlue);
	Ghost fOrange(factoryOrange);
	Field fFiled(factoryField);
}

Factory::~Factory()
{
}
