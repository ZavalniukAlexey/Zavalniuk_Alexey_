#pragma once
#include "TestApp.h"
#include "Field.h"
#include "Pacman.h"
#include "ghost.h"
#include <Windows.h>

const int padding_top = 4;
const int padding_side = 1;
bool btnClicked = false;
bool endGame = false;
char bufferScore[28];
char bufferLifes[28];
Field field;
int countStarsTemp = 0;
int score = 0;
bool firstIteration = true;
int tempScore = 0;
bool updScore = false;
bool resScore = false;
int counterTime = 0;
int counterScatter = 0;
int counterFrighten = 0;
int num = 0;
Pacman pacman(2,29,3,'@');
ghost red(12,11,1, 'r');
ghost pink(13,11,1, 'p');
ghost blue(14,11,1, 'b');
ghost orange(15,11,1, 'o');
bool step = false;
int speed = 0;
int stepSpeed = 2;

bool nextStep()
{
	speed += stepSpeed;
	if (speed == 30)
	{
		speed = 0;
		step = true;
	}
	return step;
}

TestApp::TestApp() : Parent(30, 38)
{
	
}

void TestApp::keyPressed(int btnCode)
{
	pacman.Move(btnCode, field);
	bool btnClicked = true;
	/*
	if (btnCode == 119) //w
	{
		if (f.getFieldChar(pacmanPosY - padding_top, pacmanPosX-padding_side) != '#')
		{
			pacmanPosY--;
		}
	}
	else if (btnCode == 115) //s
	{
		if (f.getFieldChar(pacmanPosY - padding_top+2, pacmanPosX-padding_side) != '#')
		{
			pacmanPosY++;
		}
	}
	else if (btnCode == 97) //a
	{
		if (f.getFieldChar(pacmanPosY - padding_top+1, pacmanPosX - padding_side - 1) != '#')
		{
			pacmanPosX--;
		}
	}
	else if (btnCode == 100) //d
	{
		if (f.getFieldChar(pacmanPosY - padding_top+1, pacmanPosX - padding_side + 1) != '#')
		{
			pacmanPosX++;
		}
	}
	//проверка упора слева
	if (pacmanPosX < padding_side + 1)
	{
		if (pacmanPosY == 13 + padding_top)
			pacmanPosX--;
		if (pacmanPosX < 2)
			pacmanPosX = X_SIZE - 3;
		pacmanPosX++;
	}
	//проверка упора справа
	if (pacmanPosX >= X_SIZE - padding_side)
	{
		if (pacmanPosY == 13 + padding_top)
			pacmanPosX++;
		if (pacmanPosX >= X_SIZE - padding_side)
			pacmanPosX = 2;
		pacmanPosX--;
	}

	//проверка упора сверху
	if (pacmanPosY < padding_top)
		pacmanPosY++;
	//проверка упора снизу
	if (pacmanPosY >= Y_SIZE - 5)
		pacmanPosY--;
*/
}

void TestApp::play(float deltaTime)
{
	//регулировка скорости
	step = nextStep();
	if (step)
	{
		//реализация поведения разбегания
		if (counterTime < 20 && num <3)
		counterTime++;
		if (counterTime == 20)
		{
			if (counterFrighten<7)
				counterFrighten++;
			if (counterFrighten == 7)
				num++;
		}
		//построение поля
		for (int i = 0; i < X_SIZE; i++)
			for (int j = 0; j < Y_SIZE; j++)
			{
				if (i == 0 || j == 0 || i == X_SIZE - padding_side || j == Y_SIZE - padding_side)
					setChar(i, j, '+');
				else if ((j < 3 && i>0 && i < 28) || ((j > X_SIZE + 3 && i > 0 && i < 28)))
					setChar(i, j, ' ');
				else
					setChar(i, j, field.getFieldChar(j - 3, i - padding_side));
			}
		if (!btnClicked)
			setChar(pacman.GetX(), pacman.GetY(), pacman.GetDisplayName());
		//проверка на столкновения

		if (pacman.GetX() == (blue.GetX() + padding_side) && pacman.GetY() == (blue.GetY() + padding_top - 1) ||
			pacman.GetX() == (orange.GetX() + padding_side) && pacman.GetY() == (orange.GetY() + padding_top - 1)||
			pacman.GetX() == (pink.GetX() + padding_side) && pacman.GetY() == (pink.GetY() + padding_top - 1)||
			pacman.GetX() == (red.GetX() + padding_side) && pacman.GetY() == (red.GetY() + padding_top - 1))
		{
			if (pacman.GetHealth() > 0)
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

		//движение призраков
		//красное приведение
		red.moveToPoint(pacman.GetX(), pacman.GetY(), field, pacman);
		
		//розовое приведение
		switch (pacman.getDirection())
		{
		case 't':
		{
			pink.moveToPoint(pacman.GetX(), pacman.GetY() - 4, field, pacman);
			break;
		}
		case 'b':
		{
			pink.moveToPoint(pacman.GetX(), pacman.GetY() + 4, field, pacman);
			break;
		}
		case 'l':
		{
			pink.moveToPoint(pacman.GetX()-4, pacman.GetY(), field, pacman);
			break;
		}
		case 'r':
		{
			pink.moveToPoint(pacman.GetX()+4, pacman.GetY(), field, pacman);
			break;
		}

		}
		// синее приведение
		blue.moveToPoint(pacman.GetX() + (pacman.GetX() - red.GetX()), pacman.GetY() + (pacman.GetY() - red.GetY()), field, pacman);
		// оранжевое приведение
		if (score%2530 > 2530/3)
			if (orange.checkDistance(pacman.GetX(), pacman.GetY(), orange.GetX(), orange.GetY()) <= 8)
				orange.moveToPoint(pacman.GetX(), pacman.GetY(), field, pacman);
			else
				orange.moveToPoint(31, 2, field, pacman);
		//конец игры

		if (endGame)
			return;

		//обновление поля при отсутствии звёзд
		if (field.countStars() == 0)
		{
			field.resetField();
			pacman.SetX(pacman.GetStartingX());
			pacman.SetY(pacman.GetStartingY());
			red.respawn();
			orange.respawn();
			blue.respawn();
			pink.respawn();
			tempScore = score;
		}

		//cчёт
		score = field.getFieldScore();
		score += tempScore;
		if (field.countStars() == 0)
			field.resetField();
		sprintf_s(bufferScore, "Score = %d", score);

		//вывод счёта и жизней
		sprintf_s(bufferLifes, "Lifes left: %d              ", pacman.GetHealth());
		for (int i = 2; i < 29; i++)
		{
			setChar(i, 1, bufferScore[i - 2]);
			setChar(i, X_SIZE + padding_top + 1, bufferLifes[i - 2]);
		}
		int sizeOfScore = 0, tempScore = score;
		while (tempScore > 0)
		{
			tempScore /= 10;
			sizeOfScore++;
		}
		for (int i = 11 + sizeOfScore; i < 29; i++)
		{
			setChar(i, 1, ' ');
		}
		step = false;
	}
}
