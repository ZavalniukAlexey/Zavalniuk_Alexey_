#include "Moving_object.h"



Moving_object::Moving_object()
{
	
}
Moving_object::Moving_object(int x, int y, int hp, char c)
{
	
}

char Moving_object::GetDisplayName()
{
	return (this->displayName_);
}

int Moving_object::GetX()
{
	return (this->PosX_);
}

int Moving_object::GetY()
{
	return (this->PosY_);
}
int Moving_object::GetStartingX()
{
	return (this->startingX_);
}
int Moving_object::GetStartingY()
{
	return (this->startingY_);
}

void Moving_object::SetX(int x)
{
	this->PosX_ = x;
}

void Moving_object::SetY(int y)
{
	this->PosY_ = y;
}

int Moving_object::GetXOld()
{
	return (this->PosXOld_);
}

int Moving_object::GetYOld()
{
	return (this->PosYOld_);
}

int Moving_object::GetHealth()
{
	return (this->health_);
}



Moving_object::~Moving_object()
{
}
