#include "FactoryPacman.hpp"

FactoryPacman::FactoryPacman()
{
	fPacman.setX(10);
	fPacman.setY(10);
	fPacman.setXOld(10);
	fPacman.setYOld(10);
	fPacman.setHealth(1);
	fPacman.setDisplayName('@');
	fPacman.setStartingX(10);
	fPacman.setStartingY(10);
	fPacman.setDirection(10);
}

FactoryPacman::FactoryPacman(Pacman p)
{
	fPacman.setX(p.getX());
	fPacman.setY(p.getY());
	fPacman.setXOld(p.getXOld());
	fPacman.setYOld(p.getYOld());
	fPacman.setHealth(p.getHealth());
	fPacman.setDisplayName(p.getDisplayName());
	fPacman.setStartingX(p.getStartingX());
	fPacman.setStartingY(p.getStartingY());
	fPacman.setDirection(p.getDirection());
}



FactoryPacman::~FactoryPacman()
{
}
