#pragma once
#include "Pacman.h"
#include "Field.h"
#include "BaseApp.h"

const int X_SIZE = 30, Y_SIZE = 38;
const int padding_top = 4;
const int padding_side = 1;


Pacman::Pacman()
{
	PosX_ = 10;
	PosY_ = 10;
	PosXOld_ = 10;
	PosYOld_ = 10;
	health_ = 3;
	displayName_ = '@';
	startingY_ = 10;
	startingX_ = 10;
}
Pacman::Pacman(int x, int y, int hp, char c)
{
	PosX_ = x;
	PosY_ = y;
	PosXOld_ = x;
	PosYOld_ = y;
	health_ = hp;
	displayName_ = c;
	startingY_ = y;
	startingX_ = x;
}

void Pacman::Move(int btnCode, Field &f)
{
	
	if (btnCode == 119) //w
	{
		if (f.getFieldChar(PosY_ - padding_top, PosX_ - padding_side) != '#')
		{
			//PosY_Old = PosY_;
			PosY_--;
		}
		this->direction_ = 't';
	}
	else if (btnCode == 115) //s
	{
		if (f.getFieldChar(PosY_ - padding_top + 2, PosX_ - padding_side) != '#')
		{
			//PosY_Old = PosY_;
			PosY_++;
		}
		this->direction_ = 'b';
	}
	else if (btnCode == 97) //a
	{
		if (f.getFieldChar(PosY_ - padding_top + 1, PosX_ - padding_side - 1) != '#')
		{
			//PosX_Old = PosX_;
			PosX_--;
		}
		this->direction_ = 'l';
	}
	else if (btnCode == 100) //d
	{
		if (f.getFieldChar(PosY_ - padding_top + 1, PosX_ - padding_side + 1) != '#')
		{
			//PosX_Old = PosX_;
			PosX_++;
		}
		this->direction_ = 'r';
	}
	//проверка упора слева
	if (PosX_ < padding_side + 1)
	{
		if (PosY_ == 13 + padding_top)
			PosX_--;
		if (PosX_ < 2)
			PosX_ = X_SIZE - 3;
		PosX_++;
	}
	//проверка упора справа
	if (PosX_ >= X_SIZE - padding_side)
	{
		if (PosY_ == 13 + padding_top)
			PosX_++;
		if (PosX_ >= X_SIZE - padding_side)
			PosX_ = 2;
		PosX_--;
	}

	//проверка упора сверху
	if (PosY_ < padding_top)
		PosY_++;
	//проверка упора снизу
	if (PosY_ >= Y_SIZE - 5)
		PosY_--;

	f.updateField(this->GetYOld() - 3, this->GetXOld() - padding_side, ' ');
	f.updateField(this->GetY() - 3, this->GetX() - padding_side, this->GetDisplayName());
	this->PosXOld_ = this->PosX_;
	this->PosYOld_ = this->PosY_;
}

void Pacman::respawn()
{
	this->health_--;
	this->PosX_ = startingX_;
	this->PosY_ = startingY_;
}

char Pacman::getDirection()
{
	return this->direction_;
}

Pacman::~Pacman()
{
}
