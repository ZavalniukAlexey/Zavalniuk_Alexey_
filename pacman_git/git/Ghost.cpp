#include "Ghost.hpp"
#include <cmath>
#include "Field.hpp"
#include "Pacman.hpp"
#include "BaseApp.hpp"
#include "Consts.hpp"

bool switched = true;

double Ghost::checkDistance(int x1, int y1, int x2, int y2)
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
	scatter_ = false;
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
	scatter_ = false;
	chase_ = true;
	direction_ = 'l';
}

void Ghost::respawn()
{
	posX_ = startingX_;
	posY_ = startingY_;
	direction_ = 'l';
}


void check(const int xGhost, const  int yGhost, const  int xPacman, const  int yPacman, double &dir, Field field)
{
	if (field.getFieldChar(yGhost, xGhost) != '#')
		dir = sqrt((xGhost - xPacman)*(xGhost - xPacman) + (yGhost - yPacman)*(yGhost - yPacman));
}

bool checkCollision(const int x, const int y,Field field)
{
	return (field.getFieldChar(y, x) == '#');
}
void chooseDirection(Ghost &ghost, const int top, const int bot, const int left, const int right)
{
	int temp = fmin(fmin(top, bot), fmin(left, right));
	if (temp == top)
	{
		ghost.setDirection('t');
	}
	else if (temp == bot)
	{
		ghost.setDirection('b');
	}
	else if (temp == right)
	{
		ghost.setDirection('r');
	}
	else if (temp == left)
	{
		ghost.setDirection('l');
	}
}
void makeAStep(Ghost &ghost, Field &field)
{
	switch (ghost.getDirection())
	{
	case 't':
	{
		ghost.setY(ghost.getY() - 1);
		break;
	}
	case 'b':
	{
		ghost.setY(ghost.getY() + 1);
		break;
	}
	case 'l':
	{
		ghost.setX(ghost.getX() - 1);
		break;
	}
	case 'r':
	{
		ghost.setX(ghost.getX() + 1);
		break;
	}
	default:
	{

	}
	}
}

void Ghost::changeDirection(const int x, const int y, Field field)
{
	double top = getBigNumber();
	double bot = getBigNumber();
	double left = getBigNumber();
	double right = getBigNumber();
	switch (direction_)
	{
	case 't':
	{
		if (!checkCollision(posX_-1, posY_, field))
		{ 
			left = checkDistance(x, y, posX_-1, posY_);
		}
		if (!checkCollision(posX_+1, posY_, field))
		{
			right = checkDistance(x, y, posX_+1, posY_);
		}
		if (!checkCollision(posX_, posY_-1, field))
		{
			top = checkDistance(x, y, posX_, posY_-1);
		}
		chooseDirection(*this, top, bot, left, right);
		makeAStep(*this, field);
		break;
	}
	case 'b':
	{
		if (!checkCollision(posX_ - 1, posY_, field))
		{
			left = checkDistance(x, y, posX_ - 1, posY_);
		}
		if (!checkCollision(posX_ + 1, posY_, field))
		{
			right = checkDistance(x, y, posX_ + 1, posY_);
		}
		if (!checkCollision(posX_, posY_ - 1, field))
		{
			top = checkDistance(x, y, posX_, posY_ - 1);
		}
		chooseDirection(*this, top, bot, left, right);
		makeAStep(*this, field);
		break;
	
	}
	case 'r':
	{
		if (!checkCollision(posX_, posY_ + 1, field))
		{
			bot = checkDistance(x, y, posX_ , posY_ + 1);
		}
		if (!checkCollision(posX_ + 1, posY_, field))
		{
			right = checkDistance(x, y, posX_ + 1, posY_);
		}
		if (!checkCollision(posX_, posY_ - 1, field))
		{
			top = checkDistance(x, y, posX_, posY_ + 1);
		}
		chooseDirection(*this, top, bot, left, right);
		makeAStep(*this, field);
		break;
	}
	case 'l':
	{
		if (!checkCollision(posX_, posY_ + 1, field))
		{
			bot = checkDistance(x, y, posX_, posY_ + 1);
		}
		if (!checkCollision(posX_ - 1, posY_, field))
		{
			left = checkDistance(x, y, posX_ - 1, posY_);
		}
		if (!checkCollision(posX_, posY_ - 1, field))
		{
			top = checkDistance(x, y, posX_, posY_ + 1);
		}
		chooseDirection(*this, top, bot, left, right);
		makeAStep(*this, field);
		break;
	}
	default:
	{
		break;
	}
	
	}
}

void move(Ghost &g, Field &f)
{
	char temp;
	g.setXOld(g.getX());
	g.setYOld(g.getY());
	switch (g.getDirection())
	{
	case 't':
	{
		g.setY(g.getY() - 1);
		temp = f.getFieldChar(g.getY(), g.getX());
		f.updateField( g.getXOld(), g.getYOld(), temp);
		f.updateField( g.getX(), g.getY(), g.getDisplayName());
		break;
	}
	case 'b':
	{
		g.setY(g.getY() + 1);
		temp = f.getFieldChar(g.getY(), g.getX());
		f.updateField(g.getXOld(), g.getYOld(), temp);
		f.updateField(g.getX(), g.getY(), g.getDisplayName());
		break;
	}
	case 'l':
	{
		if (g.getX() == 1 && g.getY() == getJumpLine())
		{
			g.setX(getXSize() - 2);
		}
		else
		{
			g.setX(g.getX() - 1);
		}
		temp = f.getFieldChar(g.getY(), g.getX());
		f.updateField(g.getXOld(), g.getYOld(), temp);
		f.updateField(g.getX(), g.getY(), g.getDisplayName());
		break;
	}
	case 'r':
	{
		if (g.getX() == getXSize() - 2 && g.getY() == getJumpLine())
		{
			g.setX(2);
		}
		else
		{
			g.setX(g.getX() + 1);
		}
		temp = f.getFieldChar(g.getY(), g.getX());
		f.updateField(g.getXOld(), g.getYOld(), temp);
		f.updateField(g.getX(), g.getY(), g.getDisplayName());
		break;
	}
	default:
	{
		
		break;
	}
	}
	
}

void Ghost::moveToStop(const int xPacman, const int yPacman, Field &field)
{
	switch (direction_)
	{
	case 't':
	{
		if (field.getFieldChar(posY_, posX_ - 1) != '#' ||
			field.getFieldChar(posY_, posX_ + 1) != '#')
		{
			changeDirection(xPacman, yPacman, field);
			break;
		}
		move(*this, field);
		break;
	}
	case 'b':
	{
		if (field.getFieldChar(posY_, posX_ - 1) != '#' ||
			field.getFieldChar(posY_, posX_ + 1) != '#')
		{
			changeDirection(xPacman, yPacman, field);
			break;
		}
		move(*this, field);
		break;
	}
	case 'l':
	{
		if (field.getFieldChar(posY_-1, posX_) != '#' ||
			field.getFieldChar(posY_+1, posX_)  != '#')
		{
			changeDirection(xPacman, yPacman, field);
			break;
		}
		move(*this, field);
		break;
	}
	case 'r':
	{
		if (field.getFieldChar(posY_ - 1, posX_) != '#' ||
			field.getFieldChar(posY_ + 1, posX_) != '#')
		{
			changeDirection(xPacman, yPacman, field);
			break;
		}
		move(*this, field);
		break;
	}
	default:
		break;
	}
	
}

void Ghost::moveToPoint(const int xPacman, const int yPAcman, Field & field)
{
	moveToStop(xPacman, yPAcman, field);
}


Ghost::~Ghost()
{
}
