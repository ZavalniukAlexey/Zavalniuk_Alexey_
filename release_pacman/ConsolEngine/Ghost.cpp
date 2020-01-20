#include "Ghost.h"
#include <cmath>
#include "Consts.h"
#include <stdlib.h>
#include <time.h>
#include "OrangeGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "RedGhost.h"
#include <memory>

double checkDistance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

Ghost::Ghost() {
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
Ghost::Ghost(int x, int y, int hp, char c) {
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

void Ghost::respawn() {
	posXOld_ = posX_ = startingX_;
	posYOld_ = posY_ = startingY_;
	direction_ = 'l';
}

void Ghost::moveToPoint(const int xPacman, const int yPacman, Field field) {
	bool crossroad = false;
	switch (direction_) {
	case 't':
	case 'b':
	{
		char t = field.getFieldChar(posX_ - 1, posY_);
		char b = field.getFieldChar(posX_ + 1, posY_);
		if ((field.getFieldChar(posX_ - 1, posY_) != '#') || ((field.getFieldChar(posX_ + 1, posY_) != '#'))) {
			crossroad = true;
		}
		break;
	}
	case 'l':
	case 'r':
	{
		char l = field.getFieldChar(posX_, posY_ - 1);
		char r = field.getFieldChar(posX_, posY_ + 1);
		if ((field.getFieldChar(posX_, posY_ - 1) != '#') || ((field.getFieldChar(posX_, posY_ + 1) != '#'))) {
			crossroad = true;
		}
		break;
	}
	default:
	{
		break;
	}
	}
	
	if (crossroad) {
		turn(field, xPacman, yPacman);
	}
	else {
		makeAStep(field);
	}
}

void Ghost::chooseDirection(const double top, const double  bot, const double left, const double right) {
	if (frighten_) {
		srand(time(NULL));
		int a = rand() % 4;
		switch (a)
		{
		case 0:
		{
			setDirection('t');
			break;
		}
		case 1:
		{	
			setDirection('r');
			break;
		}
		case 2:
		{
			setDirection('b');
			break;
		}
		case 3:
		{
			setDirection('l');
			break;
		}
		default:
			break;
		}
	}
	else {
		double temp = fmin(fmin(top, bot), fmin(left, right));
		if (temp == top) {
			setDirection('t');
		}
		else if (temp == left) {
			setDirection('l');
		}
		else if (temp == bot) {
			setDirection('b');
		}
		else if (temp == right) {
			setDirection('r');
		}
	}
}

bool collision(int x, int y, Field field) {
	return (field.getFieldChar(x, y) == '#');
}
void Ghost::turn(Field field, const int xPacman, const int yPacman) {
	double top = getBigNumber();
	double bot = getBigNumber();
	double left = getBigNumber();
	double right = getBigNumber();
	switch (direction_)	{
	case 't':
	{
		if (!collision(posX_ - 1, posY_, field)) {
			top = checkDistance(posX_ - 1, posY_, xPacman, yPacman);
		}

		if (!collision(posX_, posY_ - 1, field)) {
			left = checkDistance(posX_, posY_ - 1, xPacman, yPacman);
		}

		if (!collision(posX_, posY_ + 1, field)) {
			right = checkDistance(posX_, posY_ + 1, xPacman, yPacman);
		}
		break;
	}
	case 'b':
	{
		if (!collision(posX_ + 1, posY_, field)) {
			bot = checkDistance(posX_ + 1, posY_, xPacman, yPacman);
		}

		if (!collision(posX_, posY_ - 1, field)) {
			left = checkDistance(posX_, posY_ - 1, xPacman, yPacman);
		}

		if (!collision(posX_, posY_ + 1, field)) {
			right = checkDistance(posX_, posY_ + 1, xPacman, yPacman);
		}
		break;
	}
	case 'l':
	{
		if (!collision(posX_ + 1, posY_, field)) {
			bot = checkDistance(posX_ + 1, posY_, xPacman, yPacman);
		}
		if (!collision(posX_ - 1, posY_, field)) {
			top = checkDistance(posX_ - 1, posY_, xPacman, yPacman);
		}

		if (!collision(posX_, posY_ - 1, field)) {
			left = checkDistance(posX_, posY_ - 1, xPacman, yPacman);
		}
		break;
	}
	case 'r':
	{
		if (!collision(posX_ + 1, posY_, field)) {
			bot = checkDistance(posX_ + 1, posY_, xPacman, yPacman);
		}

		if (!collision(posX_, posY_ + 1, field)) {
			right = checkDistance(posX_, posY_ + 1, xPacman, yPacman);
		}

		if (!collision(posX_ - 1, posY_, field)) {
			top = checkDistance(posX_ - 1, posY_, xPacman, yPacman);
		}
		break;
	}
	default:
		break;
	}
	chooseDirection(top, bot, left, right);
	makeAStep(field);
}


Ghost::~Ghost() {
}

std::shared_ptr<Ghost> Ghost::createGhosts(const char type) {
	std::shared_ptr<Ghost> ghost(new Ghost);
	switch (type)
	{
	case 'R':
	{
		std::shared_ptr<Ghost> red(new RedGhost);
		ghost = red;
		break;
	}
	case 'P':
	{
		std::shared_ptr<Ghost> pink(new PinkGhost);
		ghost = pink;
		break;
	}
	case 'B':
	{
		std::shared_ptr<Ghost> blue(new BlueGhost);
		ghost = blue;
		break;
	}
	case 'O':
	{
		std::shared_ptr<Ghost> orange(new OrangeGhost);
		ghost = orange;
		break;
	}
	default:
	{
		break;
	}

	return ghost;
	}
}

void Ghost::move(const int xPacman, const int yPacman, const Field F) {
}

/*void Ghost::move(const int xPacman, const int yPacman, const char dirPacman, Field filed)
{
}

void Ghost::move(const int xPacman, const int yPacman, const int xRed, const int yRed, Field field)
{
}*/

void Ghost::setScare( bool state) {
	frighten_ = state;
}

void Ghost::setScatter(bool state) {
	scatter_ = state;
}

bool Ghost::getScatter() {
	return scatter_;
}

bool Ghost::getScare() {
	return frighten_;
}
