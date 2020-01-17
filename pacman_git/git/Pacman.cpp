
#include "Pacman.hpp"
#include "Field.hpp"
#include "BaseApp.hpp"
#include "Consts.hpp"

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
}

void Pacman::move(int btnCode, Field &f)
{
	
	if (btnCode == getWCode())
	{
		if (f.getFieldChar(posY_ - getPaddingTop(), posX_ - getPaddingSide()) != '#')
		{
			posY_--;
		}
		direction_ = 't';
	}
	else if (btnCode == getSCode())
	{
		if (f.getFieldChar(posY_ - getPaddingTop() + 2, posX_ - getPaddingSide()) != '#')
		{
			posY_++;
		}
		direction_ = 'b';
	}
	else if (btnCode == getACode())
	{
		if (f.getFieldChar(posY_ - getPaddingTop() + 1, posX_ - getPaddingSide() - 1) != '#')
		{

			posX_--;
		}
		direction_ = 'l';
	}
	else if (btnCode == getDCode())
	{
		if (f.getFieldChar(posY_ - getPaddingTop() + 1, posX_ - getPaddingSide() + 1) != '#')
		{

			posX_++;
		}
		direction_ = 'r';
	}

	if (posX_ < getPaddingSide() + 1)
	{
		if (posY_ == getJumpLine() + getPaddingTop())
		{
			posX_--;
		}
		if (posX_ < 2)
		{
			posX_ = getXSize() - 2;
		}
		posX_++;
	}

	if (posX_ >= getXSize() - getPaddingSide())
	{
		if (posY_ == getJumpLine() + getPaddingTop())
		{
			posX_++;
		}
		if (posX_ >= getXSize() - getPaddingSide())
		{
			posX_ = 2;
		}
		posX_--;
	}


	if (posY_ < getPaddingTop())
	{
		posY_++;
	}

	if (posY_ >= getYSize() - getPaddingTop()-1)
	{
		posY_--;
	}
	f.updateField(getYOld() - getPaddingTop() + 1, getXOld() - getPaddingSide(), ' ');
	f.updateField(getY() - getPaddingTop() + 1, getX() - getPaddingSide(), getDisplayName());
	posXOld_ = posX_;
	posYOld_ = posY_;
}

void Pacman::respawn()
{
	health_--;
	posX_ = startingX_;
	posY_ = startingY_;
}

char Pacman::getDirection() const
{
	return direction_;
}

Pacman::~Pacman()
{
}
