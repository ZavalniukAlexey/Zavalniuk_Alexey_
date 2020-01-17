#pragma once
#include "FactoryMovableObject.hpp"
#include "Pacman.hpp"
class FactoryPacman:
	public FactoryMovableObject
{
private: 
	Pacman fPacman;
public:
	FactoryPacman();
	FactoryPacman(Pacman p);
	~FactoryPacman();
};

