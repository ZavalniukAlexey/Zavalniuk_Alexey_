#include "Pacman.h"
#include "Field.h"

Pacman::Pacman()
{
	posXOld_ = startingX_ = posX_ = 29;
	posYOld_ = startingY_= posY_ = 2;
	health_ = 3;
	displayName_ = '@';
	direction_ = 't';
	energised_ = false;
}
Pacman::Pacman(const int x, const  int y, const  int hp, const  char c)
{
	posX_ = x;
	posY_ = y;
	posXOld_ = x;
	posYOld_ = y;
	health_ = hp;
	displayName_ = c;
	startingY_ = y;
	startingX_ = x;
	direction_ = 'b';
	energised_ = false;
}
void checkCollision(const Field field, char direction)
{

}

void Pacman::respawn()
{
	health_--;
	posX_ = startingX_;
	posY_ = startingY_;
	direction_ = 't';
}

Pacman::~Pacman()
{
}
