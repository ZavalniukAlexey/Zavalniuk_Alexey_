#pragma once
#include "Game.hpp"
#include "Field.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "Consts.hpp"
#include <Windows.h>







Game::Game() : Parent(getConsoleSizeX(), getConsoleSizeY())
{
	
}

int Game::getX() const
{
	return  X_SIZE;
}

int Game::getY() const
{
	return  Y_SIZE;
}

void Game::keyPressed(Pacman &pacman, int btnCode, Field &field)
{
	pacman.move(btnCode, field);	
}

bool checkCollision(Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange)
{
	return (pacman.getX() == (red.getX() + getPaddingSide()) && pacman.getY() == (red.getY() + getPaddingTop() - 1) ||
		(pacman.getX() == (pink.getX() + getPaddingSide()) && pacman.getY() == (red.getY() + getPaddingTop() - 1)) ||
		(pacman.getX() == (blue.getX() + getPaddingSide()) && pacman.getY() == (blue.getY() + getPaddingTop() - 1)) ||
		(pacman.getX() == (orange.getX() + getPaddingSide()) && pacman.getY() == (orange.getY() + getPaddingTop() - 1)));
}
void collision(Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange)
{
	if ((pacman.getHealth() > 0) && checkCollision(pacman, red, pink, blue, orange))
	{
		pacman.respawn();
		red.respawn();
		pink.respawn();
		blue.respawn();
		orange.respawn();
	}
}

void DrawLine(Game &game, Field &field, int i)
{
	for (int j = 0; j < getYSize(); j++)
	{
		if (i == 0 || j == 0 || i == getXSize() - getPaddingSide() || j == getYSize() - getPaddingTop())
		{
			game.setChar(i, j, '+');
		}
		else if ((j < getPaddingBot() && i>0 && i < getXSize()) || (j > getXSize() + getPaddingTop() - 1 && i > 0 && i < getYSize()))
		{
			game.setChar(i, j, ' ');
		}
		else
		{
			game.setChar(i, j, field.getFieldChar(j - getPaddingTop() + 1, i - getPaddingSide()));
		}
	}
}

void drawField(Game &game, Field &field)
{
	int num = getXSize()*getYSize();

	for (int i = 0; i < getXSize(); i++)
	{
		DrawLine(game, field, i);
	}
}


void workWithScoreAndLifes(Game &game, Field &field, Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange, int &score)
{
	static int tempScore = 0;
	char bufferScore[28];
	char bufferLifes[28];
	score = field.getFieldScore();
	score += tempScore;
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
	
	if (field.countStars() == 0)
	{
		field.resetField();
	}
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

void moveObjects(Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange, Field &field, int score)
{
	collision(pacman, red, pink, blue, orange);

	if (pacman.getHealth()==0)
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

	if (score % getMaxScore() > getScoreToSpawnBlue())
	{
		blue.moveToPoint(pacman.getX() + (pacman.getX() - red.getX()), pacman.getY() + (pacman.getY() - red.getY()), field, pacman);
	}
	if (score % getMaxScore() > getMaxScore() / 3)
	{
		if (orange.checkDistance(pacman.getX(), pacman.getY(), orange.getX(), orange.getY()) <= 8)
		{
			orange.moveToPoint(pacman.getX(), pacman.getY(), field, pacman);
		}
		else
		{
			orange.moveToPoint(31, 2, field, pacman);
		}
	}

}


int speed = 0;
void Game::play(float deltaTime, Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange, Field &field)
{
	bool step = !(speed < 65);
	if (step) {
		int score = 0;
		drawField(*this, field);
		setChar(pacman.getX(), pacman.getY(), pacman.getDisplayName());
		moveObjects(pacman, red, pink, blue, orange, field, score);
		workWithScoreAndLifes(*this, field, pacman, red, pink, blue, orange, score);
	}
	speed += 5;
}
