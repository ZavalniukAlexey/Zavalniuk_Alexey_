#include "Game.h"
#include "Consts.h"
Game::Game() : Parent(setFieldY()-2, setFieldX()-2)
{

}

void Game::KeyPressed(int btnCode)
{
	
	char s = field_.getFieldChar(pacman_.getX() - 1, pacman_.getY());
	if ((btnCode == getWCode() || btnCode == getUpCode()) && field_.getFieldChar(pacman_.getX() - 1, pacman_.getY()) != '#')
	{
		pacman_.setDirection('t');
	}
	else if ((btnCode == getSCode() || btnCode == getDownCode()) && field_.getFieldChar(pacman_.getX() + 1, pacman_.getY()) != '#') 
	{
		pacman_.setDirection('b');
	}
	else if ((btnCode == getACode() || btnCode == getLeftCode()) && field_.getFieldChar(pacman_.getX(), pacman_.getY()-1) != '#')
	{
		pacman_.setDirection('l');
	}
	else if ((btnCode == getDCode() || btnCode == getRightCode()) && field_.getFieldChar(pacman_.getX(), pacman_.getY()+1) != '#') 
	{
		pacman_.setDirection('r');
	}
}
int speed = 0;
int step = 7;
void Game::UpdateF(float deltaTime)
{

	bool nextStep = false;
	speed += step;
	if (speed > 50)
	{
		speed %= 50;
		nextStep = true;
	}
	if (nextStep)
	{
		//drawField
		for (int i = 0; i < setFieldX() - 1; i++)
			for (int j = 0; j < setFieldY() - 1; j++)
				SetChar(j, i, field_.getFieldChar(i, j));

		pacman_.makeAStep(field_);

		rg_.move(pacman_.getX(), pacman_.getY(), field_);
		SetChar(rg_.getY(), rg_.getX(), rg_.getDisplayName());

		pg_.move(pacman_.getX(), pacman_.getY(), pacman_.getDirection(), field_);
		SetChar(pg_.getY(), pg_.getX(), pg_.getDisplayName());

		if (score%getMaxScore() > getScoreToSpawnBlue())
		{
			bg_.move(pacman_.getX(), pacman_.getY(), rg_.getX(), rg_.getY(), field_);
			SetChar(bg_.getY(), bg_.getX(), bg_.getDisplayName());
		}

		if (score - level_*getMaxScore() > getScoreToSpawnOrange());
		{
			og_.move(pacman_.getX(), pacman_.getY(), field_);
			SetChar(og_.getY(), og_.getX(), og_.getDisplayName());
		}

		//count score
		if (field_.getFieldChar(pacman_.getX(), pacman_.getY()) == '.')
			score += 10;

		//счёт и жизни
		int ScoreSize = 0;
		int temp = score;
		while (temp /= 10)
		{
			ScoreSize++;
		}
		char bufScore[10];
		char bufHealth[10];
		sprintf_s(bufScore, "%d", score);
		sprintf_s(bufHealth, "%d", pacman_.getHealth());
		for (int i = 0; i < 10; i++)
		{
			SetChar(11 + i, 1, bufScore[i]);
			SetChar(16 + i, 34, bufHealth[i]);

		}
		//передвижение пакмена по полю
		field_.setFieldChar(pacman_.getXOld(), pacman_.getYOld(), ' ');
		field_.setFieldChar(pacman_.getX(), pacman_.getY(), pacman_.getDisplayName());
		pacman_.setXOld(pacman_.getX());
		pacman_.setYOld(pacman_.getY());
	}
}
