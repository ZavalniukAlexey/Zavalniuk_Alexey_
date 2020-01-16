#pragma once
#include "Game.hpp"
#include "Field.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "Consts.hpp"
#include <Windows.h>


bool btnClicked = false;
bool endGame = false;
bool firstIteration = true;
bool step = false;

int speed = 0;
int score = 0;

bool nextStep()
{
	speed += getStepSpeed();
	if (speed == getMaxSpeed())
	{
		speed = 0;
		step = true;
	}
	return step;
}

Game::Game() : Parent(30, 38)
{
	
}

int Game::getX() const
{
	return this->X_SIZE;
}

int Game::getY() const
{
	return this->Y_SIZE;
}

void Game::keyPressed(Pacman &pacman, int btnCode, Field &field)
{
	pacman.move(btnCode, field);	
}

void collision(Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange)
{
	if (pacman.getX() == (red.getX() + getPaddingSide()) && pacman.getY() == (red.getY() + getPaddingTop() - 1)||
		pacman.getX() == (pink.getX() + getPaddingSide()) && pacman.getY() == (red.getY() + getPaddingTop() - 1||
		pacman.getX() == (blue.getX() + getPaddingSide()) && pacman.getY() == (blue.getY() + getPaddingTop() - 1)||
		pacman.getX() == (orange.getX() + getPaddingSide()) && pacman.getY() == (orange.getY() + getPaddingTop() - 1)))
	{
		if (pacman.getHealth() > 0)
		{
			pacman.respawn();
			red.respawn();
			pink.respawn();
			blue.respawn();
			orange.respawn();
			firstIteration = true;
		}
		else
			endGame = true;
	}
}

void drawField(Game &game, Field &field)
{
	for (int i = 0; i < getXSize(); i++)
	{
		for (int j = 0; j < getYSize(); j++)
		{
			if (i == 0 || j == 0 || i == getXSize() - getPaddingSide() || j == getYSize() - getPaddingTop())
				game.setChar(i, j, '+');
			else if ((j < getPaddingBot() && i>0 && i < getXSize()) || (j > getXSize() + 3 && i > 0 && i < getYSize()))
				game.setChar(i, j, ' ');
			else
				game.setChar(i, j, field.getFieldChar(j - getPaddingTop() + 1, i - getPaddingSide()));
		}
	}
}

int tempScore = 0;
void workWithScoreAndLifes(Game &game, Field &field, Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange)
{
	char bufferScore[28];
	char bufferLifes[28];
	if (field.countStars() == 0)
	{
		field.resetField();
		pacman.setX(pacman.getStartingX());
		pacman.setY(pacman.getStartingY());
		red.respawn();
		orange.respawn();
		blue.respawn();
		pink.respawn();
		tempScore = score;
	}
	score = field.getFieldScore();
	score += tempScore;
	if (field.countStars() == 0)
		field.resetField();
	sprintf_s(bufferScore, "Score = %d", score);

	sprintf_s(bufferLifes, "Lifes left: %d             ", pacman.getHealth());

	for (int i = 2; i < 29; i++)
	{
		game.setChar(i, 1, bufferScore[i - 2]);
		game.setChar(i, game.getX() + getPaddingTop() + 1, bufferLifes[i - 2]);
	}
	int sizeOfScore = 0;
	int tempTemp = score;
	while (tempTemp > 0)
	{
		tempTemp /= 10;
		sizeOfScore++;
	}
	for (int i = 11 + sizeOfScore; i < 29; i++)
	{
		game.setChar(i, 1, ' ');
	}
}

void moveObjects(Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange, Field &field)
{
	collision(pacman, red, pink, blue, orange);

	if (endGame)
	{
		return;
	}

	red.moveToPoint(pacman.getX(), pacman.getY(), field, pacman);

	switch (pacman.getDirection())
	{
	case 't':
	{
		pink.moveToPoint(pacman.getX(), pacman.getY() - 4, field, pacman);
		break;
	}
	case 'b':
	{
		pink.moveToPoint(pacman.getX(), pacman.getY() + 4, field, pacman);
		break;
	}
	case 'l':
	{
		pink.moveToPoint(pacman.getX() - getPaddingTop(), pacman.getY(), field, pacman);
		break;
	}
	case 'r':
	{
		pink.moveToPoint(pacman.getX() + getPaddingTop(), pacman.getY(), field, pacman);
		break;
	}
	default:
		pink.moveToPoint(2, -2, field, pacman);
	}
	if (score % 2530 > 300)
	{
		blue.moveToPoint(pacman.getX() + (pacman.getX() - red.getX()), pacman.getY() + (pacman.getY() - red.getY()), field, pacman);
	}
	if (score % 2530 > 2530 / 3)
	{
		if (orange.checkDistance(pacman.getX(), pacman.getY(), orange.getX(), orange.getY()) <= 8)
			orange.moveToPoint(pacman.getX(), pacman.getY(), field, pacman);
		else
			orange.moveToPoint(31, 2, field, pacman);
	}

}

void Game::play(float deltaTime, Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange, Field &field)
{

	step = nextStep();
	if (step)
	{
		drawField(*this, field);
		if (!btnClicked)
			setChar(pacman.getX(), pacman.getY(), pacman.getDisplayName());
		moveObjects(pacman, red, pink, blue, orange, field);
		workWithScoreAndLifes(*this, field, pacman, red, pink, blue, orange);
		step = false;
	}
}
