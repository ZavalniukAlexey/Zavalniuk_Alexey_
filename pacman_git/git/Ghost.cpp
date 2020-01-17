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

void move(Ghost &g, const int x, const int y, Field &f, char dir)
{
	char temp;
	g.setXOld(g.getX());
	g.setYOld(g.getY());
	switch (dir)
	{
	case 't':
	{
		g.setY(g.getY() - 1);
		break;
	}
	case 'b':
	{
		g.setY(g.getY() + 1);
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
			g.setX(g.getX()-1);
		}
		
		break;
	}
	case 'r':
	{
		if (g.getX() == getXSize()-2 && g.getY() == getJumpLine())
		{
			g.setX(2);
		}
		else
		{
			g.setX(g.getX() + 1);
		}
		break;
	}
	default:
	{
		g.setY(g.getY() + 1);
		break;
	}
	}
	temp = f.getFieldChar(g.getY(), g.getX());
	f.updateField(g.getYOld(), g.getXOld(), temp);
	f.updateField(g.getY(), g.getX(), g.getDisplayName());
}

void Ghost::moveToStop(Field &field, int steps, Pacman pacman)
{
	switch (direction_)
	{
	case 't':
	{
		if (!switched)
		{
			if (field.getFieldChar(posY_,  posX_ - 1) != '#' ||
				field.getFieldChar( posY_,  posX_ + 1) != '#')
			{
				turn('t', pacman, field);
				break;
			}
		}
		switched = false;
		while (steps-- && (field.getFieldChar( posY_ - 1,  posX_) != '#'))
		{
			move(*this,  posY_ - 1,  posX_, field, 't');
		}
		break;
	}
	case 'b':
	{
		if (!switched)
		{
			if (field.getFieldChar( posY_,  posX_ - 1) != '#' ||
				field.getFieldChar( posY_,  posX_ + 1) != '#')
			{
				turn('b', pacman, field);
				break;
			}
		}
		switched = false;
		while (steps-- && (field.getFieldChar( posY_ + 1,  posX_) != '#'))
		{
			move(*this,  posY_ + 1,  posX_, field, 'b');
		}
		break;
	}
	case 'l':
	{
		if (!switched)
		{
			if (field.getFieldChar( posY_ - 1,  posX_) != '#' ||
				field.getFieldChar( posY_ + 1,  posX_) != '#')
			{
				turn('l', pacman, field);
				break;
			}
		}
		switched = false;
		while (steps-- && (field.getFieldChar( posY_,  posX_ - 1) != '#'))
		{
			move(*this,  posY_,  posX_ - 1, field, 'l');
		}
		break;
	}
	case 'r':
	{
		if (!switched)
		{
			if (field.getFieldChar( posY_ - 1,  posX_) != '#' ||
				field.getFieldChar( posY_ + 1,  posX_) != '#')
			{
				turn('r', pacman, field);
				break;
			}
		}
		switched = false;
		while (steps-- && (field.getFieldChar( posY_,  posX_ + 1) != '#'))
		{
			move(*this,  posY_,  posX_ + 1, field, 'r');
		}
		break;
	}

	default:
	{
		move(*this,  posY_,  posX_ + 1, field, 'r');
		break;
	}
	}
}

void check(const int xGhost, const  int yGhost, const  int xPacman, const  int yPacman, double &dir, Field field)
{
	if (field.getFieldChar(yGhost, xGhost) != '#')
		dir = sqrt((xGhost - xPacman)*(xGhost - xPacman) + (yGhost - yPacman)*(yGhost - yPacman));
}

void set(const double top, const double bot, const double right, const double left, Field field, Ghost& ghost)
{
	double temp = fmin(fmin(top, bot), fmin(right, left));
	if (top == temp)
	{
		if (field.getFieldChar(ghost.getY() - 1, ghost.getX()) != '#')
		{
			ghost.setDirection('t');
		}
		else
			temp = fmin(bot, fmin(left, right));
	}
	else if (left == temp)
	{
		if (field.getFieldChar(ghost.getY(), ghost.getX() - 1) != '#')
		{
			ghost.setDirection('l');
		}
		else
		{
			temp = fmin(bot, right);
		}
	}
	else if (right == temp)
	{
		if (field.getFieldChar(ghost.getY(), ghost.getX() + 1) != '#')
		{
			ghost.setDirection('r');
		}
		else
		{
			temp = bot;
		}
	}
	else 
	{
		if (field.getFieldChar(ghost.getY() + 1, ghost.getX()) != '#')
		{
			ghost.setDirection('b');
		}
	}
}
void Ghost::turn(char direction, Pacman pacman, Field field)
{
	switched = true;
	double top = getBigNumber(), bot = getBigNumber(), right = getBigNumber(), left = getBigNumber();
	switch (direction)
	{
	case 't':
	{
		check( getX(),  getY() - 1, pacman.getX(), pacman.getY(), top, field);
		check( getX() + 1,  getY(), pacman.getX(), pacman.getY(), right, field);
		check( getX() - 1,  getY(), pacman.getX(), pacman.getY(), left, field);
		set(top, bot, right, left, field, *this);
		break;
	}
	case 'b':
	{
		check( getX() + 1,  getY(), pacman.getX(), pacman.getY(), right, field);
		check( getX() - 1,  getY(), pacman.getX(), pacman.getY(), left, field);
		check( getX(),  getY() + 1, pacman.getX(), pacman.getY(), bot, field);
		set(top, bot, right, left, field, *this);
		break;
	}
	case 'r':
	{
		check( getX(),  getY() + 1, pacman.getX(), pacman.getY(), bot, field);
		check( getX() + 1,  getY(), pacman.getX(), pacman.getY(), right, field);
		check( getX(),  getY() - 1, pacman.getX(), pacman.getY(), top, field);
		set(top, bot, right, left, field, *this);
		break;
	}
	case 'l':
	{
		check( getX(),  getY() - 1, pacman.getX(), pacman.getY(), top, field);
		check( getX() - 1,  getY(), pacman.getX(), pacman.getY(), left, field);
		check( getX(),  getY() + 1, pacman.getX(), pacman.getY(), bot, field);
		set(top, bot, right, left, field, *this);
		break;
	}
	default:
	{
		bot = 1;
		set(top, bot, right, left, field, *this);
	}
	}

}

void Ghost::moveToPoint(const int x, const  int y, Field &field, Pacman pacman)
{
	moveToStop(field, 1, pacman);
}

Ghost::~Ghost()
{
}
