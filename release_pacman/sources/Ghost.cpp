#include "Ghost.h"
#include <cmath>
#include "Consts.h"

double checkDistance(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

Ghost::Ghost()
{
	posX_ = 20;
	posY_ = 6;
	posXOld_ = posX_;
	posYOld_ = posY_;
	health_ = 1;
	displayName_ = 'o';
	startingY_ = 6;
	startingX_ = 20;
	frighten_ = false;
	chase_ = true;
	direction_ = 'l';
}
Ghost::Ghost(int x, int y, int hp, char c)
{
	posX_ = x;
	posY_ = y;
	posXOld_ = x;
	posYOld_ = y;
	health_ = hp;
	displayName_ = c;
	startingY_ = y;
	startingX_ = x;
	frighten_ = false;
	chase_ = true;
	direction_ = 'l';
}

void Ghost::respawn()
{
	posXOld_ = posX_ = startingX_;
	posYOld_ = posY_ = startingY_;
	direction_ = 'l';
}

void Ghost::moveToPoint(const int xPacman, const int yPacman, Field field)
{
	bool crossroad = false;
	switch (direction_)
	{
	case 't':
	case 'b':
	{
		char t = field.getFieldChar(posX_ - 1, posY_);
		char b = field.getFieldChar(posX_ + 1, posY_);
		if ((field.getFieldChar(posX_ - 1, posY_) != '#') || ((field.getFieldChar(posX_ + 1, posY_) != '#')))
			crossroad = true;
		break;
	}
	case 'l':
	case 'r':
	{
		char l = field.getFieldChar(posX_, posY_ - 1);
		char r = field.getFieldChar(posX_, posY_ + 1);
		if ((field.getFieldChar(posX_, posY_-1) != '#') || ((field.getFieldChar(posX_, posY_+1) != '#')))
			crossroad = true;
		break;
	}
	default:
		break;
	}
	
	if (crossroad)
	{
		turn(field, xPacman, yPacman);
	}
	else
	{
		makeAStep(field);
	}
}

void Ghost::chooseDirection(const double top, const double  bot, const double left, const double right)
{
	double temp = fmin(fmin(top, bot), fmin(left, right));
	if (temp == top)
	{
		setDirection('t');
	}

	else if (temp == left)
	{
		setDirection('l');
	}
	else if (temp == bot)
	{
		setDirection('b');
	}
	else if (temp == right)
	{
		setDirection('r');
	}

}

bool collision(int x, int y, Field field)
{
	return (field.getFieldChar(x, y) == '#');
}
void Ghost::turn(Field field, const int xPacman, const int yPacman)
{
	double top = getBigNumber();
	double bot = getBigNumber();
	double left = getBigNumber();
	double right = getBigNumber();
	switch (direction_)
	{
		//check collision
	case 't':
	{
		if (!collision(posX_ - 1, posY_, field))
			top = checkDistance(posX_ - 1, posY_, xPacman, yPacman);

		if (!collision(posX_, posY_ - 1, field))
			left = checkDistance(posX_, posY_-1, xPacman, yPacman);

		if (!collision(posX_, posY_ + 1, field))
			right = checkDistance(posX_, posY_+1, xPacman, yPacman);
		break;
	}
	case 'b':
	{
		if (!collision(posX_ + 1, posY_, field))
			bot = checkDistance(posX_ + 1, posY_, xPacman, yPacman);

		if (!collision(posX_, posY_ - 1, field))
			left = checkDistance(posX_, posY_ - 1, xPacman, yPacman);

		if (!collision(posX_, posY_ + 1, field))
			right = checkDistance(posX_, posY_ + 1, xPacman, yPacman);
		break;
	}
	case 'l':
	{
		if(!collision(posX_ + 1, posY_, field))
			bot = checkDistance(posX_ + 1, posY_, xPacman, yPacman);
		if (!collision(posX_ - 1, posY_, field))
			top = checkDistance(posX_ - 1, posY_, xPacman, yPacman);

		if (!collision(posX_, posY_ - 1, field))
			left = checkDistance(posX_, posY_ - 1, xPacman, yPacman);
		break;
	}
	case 'r':
	{
		if (!collision(posX_ + 1, posY_, field))
			bot = checkDistance(posX_ + 1, posY_, xPacman, yPacman);

		if (!collision(posX_, posY_ + 1, field))
			right = checkDistance(posX_, posY_ + 1, xPacman, yPacman);

		if (!collision(posX_ - 1, posY_, field))
			top = checkDistance(posX_-1, posY_, xPacman, yPacman);
		break;
	}
	default:
		break;
	}
	chooseDirection(top, bot, left, right);
	makeAStep(field);
}


Ghost::~Ghost()
{
}

void Ghost::move(const int xPacman, const int yPacman, const Field F)
{
	moveToPoint(xPacman, yPacman, F);
}
