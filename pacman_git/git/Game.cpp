#pragma once
#include "Game.hpp"
#include "BlueGhost.hpp"
#include "RedGhost.hpp"
#include "PinkGhost.hpp"
#include "OrangeGhost.hpp"
#include "Pacman.hpp"
#include "Field.hpp"
#include "Consts.hpp"
#include <Windows.h>

Game::Game() : Parent(getConsoleSizeX(), getConsoleSizeY())
{
	
}

Game::Game(Pacman pacman, RedGhost red, PinkGhost pink, BlueGhost blue, OrangeGhost orange, Field field) : Parent(getConsoleSizeX(), getConsoleSizeY())
{
	pacman_ = pacman;
	red_ = red;
	pink_ = pink;
	blue_ = blue;
	orange_ = orange;
	field_ = field;
}

int Game::getX() const
{
	return X_SIZE;
}

int Game::getY() const
{
	return Y_SIZE;
}

void Game::setPacman(Pacman p)
{
	pacman_ = p;
}

void Game::setRed(RedGhost r)
{
	red_ = r;
}

void Game::setPink(PinkGhost p)
{
	pink_ = p;
}

void Game::setBlue(BlueGhost b)
{
	blue_ = b;
}

void Game::setOrange(OrangeGhost o)
{
	orange_ = o;
}

void Game::setField(Field F)
{
	field_ = F;
}

void Game::keyPressed(Pacman &pacman, int btnCode, Field &field)
{
	pacman.turn(btnCode, field);
	this->setPacman(pacman);
	this->setField(field);
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


void workWithScoreAndLifes(Game &game, Field &field, Pacman &pacman, RedGhost &red, PinkGhost &pink, BlueGhost &blue, OrangeGhost &orange, int &score)
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

void moveObjects(Pacman &pacman, RedGhost &red, PinkGhost &pink, BlueGhost &blue, OrangeGhost &orange, Field &field, int score)
{
	collision(pacman, red, pink, blue, orange);

	if (pacman.getHealth()==0)
	{
		return;
	}
	red.moveToPoint(pacman.getX(), pacman.getY(), field);
	pink.moveToPoint(pacman.getX(), pacman.getY(), pacman.getDirection(), field);
	blue.moveToPoint(pacman.getX(), pacman.getY(), red.getX(), red.getY(), field);
	orange.moveToPoint(pacman.getX(), pacman.getY(), field);
}

int speed = 0;
void Game::play(float deltaTime)
{
	static int score = 0;
	bool step = !(speed < 65);
	if (step) {
		Pacman P = getPacman();
		RedGhost RG = getRedghost();
		PinkGhost PG =getPinkghost();
		BlueGhost BG = getBlueghost();
		OrangeGhost OG = getOrangeghost();
		Field F = getField();
		drawField(*this, F);
		setChar(P.getX(), P.getY(), P.getDisplayName());
		moveObjects(P, RG,  PG, BG, OG, F, score);
		workWithScoreAndLifes(*this, F, P, RG, PG, BG, OG, score);
		setChar(P.getY(), P.getX(), '@');
		setChar(RG.getY(), RG.getX(), 'R');
		setChar(PG.getY(), PG.getX(), 'P');
		setChar(BG.getY(), BG.getX(), 'B');
		setChar(OG.getY(), OG.getX(), 'O');
		setPacman(P);
		setBlue(BG);
		setOrange(OG);
		setPacman(P);
		setPink(PG);
		setRed(RG);
	}
	
	speed += 5;
}
