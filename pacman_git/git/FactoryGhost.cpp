#include "FactoryGhost.hpp"



FactoryGhost::FactoryGhost()
{
	fGhost.setX(10);
	fGhost.setY(10);
	fGhost.setXOld(10);
	fGhost.setYOld(10);
	fGhost.setHealth(1);
	fGhost.setDisplayName('@');
	fGhost.setStartingX(10);
	fGhost.setStartingY(10);
	fGhost.setDirection(10);
}

FactoryGhost::FactoryGhost(Ghost gh)
{
	fGhost.setX(gh.getX());
	fGhost.setY(gh.getY());
	fGhost.setXOld(gh.getXOld());
	fGhost.setYOld(gh.getYOld());
	fGhost.setHealth(gh.getHealth());
	fGhost.setDisplayName(gh.getDisplayName());
	fGhost.setStartingX(gh.getStartingX());
	fGhost.setStartingY(gh.getStartingY());
	fGhost.setDirection(gh.getDirection());
}

FactoryGhost::~FactoryGhost()
{

}
