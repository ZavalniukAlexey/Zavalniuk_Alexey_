
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

void Pacman::turn(int btnCode, Field &field)
{
	
	if((btnCode == getWCode() || btnCode == getUpCode()))// && field.getFieldChar(posX_ - getPaddingSide(), posY_ - getPaddingTop() ) != '#')
	{
		this->direction_ = 't';
	}
	else if ((btnCode == getACode() || btnCode == getLeftCode()))// && field.getFieldChar(posY_ - getPaddingTop() + 1, posX_ - getPaddingSide() - 1) != '#'))
	{
		this->direction_ = 'l';
	}
	else if ((btnCode == getSCode() || btnCode == getDownCode()))// && field.getFieldChar(posY_ - getPaddingTop() + 2, posX_ - getPaddingSide()) != '#')
	{
		this->direction_ = 'b';
	}
	else if ((btnCode == getDCode() || btnCode == getRightCode()))// && field.getFieldChar(posY_ - getPaddingTop() + 1, posX_ - getPaddingSide() + 1) != '#')
	{
		direction_ = 'r';
	}
	move(field);
	//int a = 0;
}

void Pacman::move(Field &field)
{
	switch (direction_) {
	case 't':
	{
		if (field.getFieldChar(posY_ - getPaddingTop(), posX_ - getPaddingSide()) != '#')
		{
			posY_--;
		}
		field.updateField(getYOld() - getPaddingTop() + 1, getXOld() - getPaddingSide(), ' ');
		field.updateField(getY() - getPaddingTop() + 1, getX() - getPaddingSide(), getDisplayName());
		this->posXOld_ = posX_;
		this->posYOld_ = posY_;
		break;
	}
	case 'b':
	{

		if (field.getFieldChar(posY_ - getPaddingTop() + 2, posX_ - getPaddingSide()) != '#')
		{
			posY_++;
		}
		field.updateField(getYOld() - getPaddingTop() + 1, getXOld() - getPaddingSide(), ' ');
		field.updateField(getY() - getPaddingTop() + 1, getX() - getPaddingSide(), getDisplayName());
		this->posXOld_ = posX_;
		this->posYOld_ = posY_;
		break;
	}
	case 'r':
	{
		if (field.getFieldChar(posY_ , posX_ + 1) != '#')
		{
			this->posX_++;
		}
		posXOld_ = posX_;
		posYOld_ = posY_;
		field.updateField(getYOld() - getPaddingTop() + 1, getXOld() - getPaddingSide(), ' ');
		field.updateField(getY() - getPaddingTop() + 1, getX() - getPaddingSide(), getDisplayName());
		
		break;
	}
	case 'l':
	{
		if (field.getFieldChar(posY_ - getPaddingTop() + 1, posX_ - getPaddingSide() - 1) != '#')
		{
			posX_--;
		}
		field.updateField(getYOld() - getPaddingTop() + 1, getXOld() - getPaddingSide(), ' ');
		field.updateField(getY() - getPaddingTop() + 1, getX() - getPaddingSide(), getDisplayName());
		posXOld_ = posX_;
		posYOld_ = posY_;
		break;
	}

	default:
	{
		break;
	}
	}
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
