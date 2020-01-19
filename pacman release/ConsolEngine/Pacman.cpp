#include "Pacman.h"
#include "Field.h"

Pacman::Pacman()
{
	posX_ = 10;
	posY_ = 10;
	posXOld_ = 10;
	posYOld_ = 10;
	health_ = 3;
	displayName_ = '@';
	startingY_ = 10;
	startingX_ = 10;
	direction_ = 'b';
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
	posXOld_ = posX_ = startingX_;
	posYOld_ = posY_ = startingY_;
}

Pacman::~Pacman()
{
}
