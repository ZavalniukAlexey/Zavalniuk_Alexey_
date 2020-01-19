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

void fixOutput(Game g, int score, int level)
{
	int ScoreSize = 0;
	while (score /=10)
	{
		ScoreSize++;
	}
	for (int i = 0; i < 10 - ScoreSize; i++)
		g.setChar(13 + ScoreSize + i, 1, ' ');

	int levelSize = 0;
	while (level /= 10)
	{
		levelSize++;
	}
	for (int i = 0; i < 10 - levelSize; i++)
		g.setChar(13 + levelSize + i, 2, ' ');
	for (int i = 0; i < 9; i++)
		g.setChar(17 + i, 34, ' ');
}
void drawField(Game g, const int score, const int hp, const int lvl, Field f)
{
	//drawField
	for (int i = 0; i < setFieldX() - 1; i++)
		for (int j = 0; j < setFieldY() - 1; j++)
			g.setChar(j, i, f.getFieldChar(i, j));
	char bufScore[10];
	char bufHealth[10];
	char bufLevel[10];
	sprintf_s(bufScore, "%d", score);
	sprintf_s(bufHealth, "%d", hp-1);
	sprintf_s(bufLevel, "%d", lvl);

	for (int i = 0; i < 10; i++)
	{
		g.setChar(11 + i, 1, bufScore[i]);
		g.setChar(16 + i, 34, bufHealth[i]);
		g.setChar(11 + i, 2, bufLevel[i]);
	}

	fixOutput(g, score, lvl);
}

bool collideObjects(Pacman &P, RedGhost &RG, PinkGhost &PG, BlueGhost &BG, OrangeGhost &OG)
{
	return (
		(P.getX() == RG.getX() && P.getY() == RG.getY()) ||
		(P.getX() == PG.getX() && P.getY() == PG.getY()) ||
		(P.getX() == BG.getX() && P.getY() == BG.getY()) ||
		(P.getX() == OG.getX() && P.getY() == OG.getY())
		);

}
void moveObjects(Game &g, Pacman &P, RedGhost &RG, PinkGhost &PG, BlueGhost &BG, OrangeGhost &OG, Field &F, const int score)
{
	P.makeAStep(F);

	if (collideObjects(P, RG, PG, BG, OG))
	{

		P.respawn();
		RG.respawn();
		PG.respawn();
		BG.respawn();
		OG.respawn();
	}

	RG.move(P.getX(), P.getY(), F);
	g.setChar(RG.getY(), RG.getX(), RG.getDisplayName());

	PG.move(P.getX(), P.getY(), P.getDirection(), F);
	g.setChar(PG.getY(), PG.getX(), PG.getDisplayName());

	if (score%getMaxScore() > getScoreToSpawnBlue())
	{
		BG.move(P.getX(), P.getY(), RG.getX(), RG.getY(), F);
		g.setChar(BG.getY(), BG.getX(), BG.getDisplayName());
	}

	if (score%getMaxScore() > getStarsToSpawnOrange() * 10)
	{
		OG.move(P.getX(), P.getY(), F);
		g.setChar(OG.getY(), OG.getX(), OG.getDisplayName());
	}
	F.setFieldChar(P.getXOld(), P.getYOld(), ' ');
	F.setFieldChar(P.getX(), P.getY(), P.getDisplayName());
	P.setXOld(P.getX());
	P.setYOld(P.getY());
	
}
void Game::UpdateF(float deltaTime)
{
	bool nextStep = false;
	speed_ += step_;
	if (speed_ > maxSpeed_)
	{
		speed_ %= maxSpeed_;
		nextStep = true;
	}
	if (nextStep)
	{
		drawField(*this, score_, pacman_.getHealth(), level_, field_);
		moveObjects(*this, pacman_, redGhost_, pinkGhost_, blueGhost_, orangeGhost_, field_, score_);

		if (pacman_.getHealth() == 0)
		{
			this->~Game();
			return;
		}

		if (field_.getFieldChar(pacman_.getX(), pacman_.getY()) == '.')
			score_ += 10;

		if (field_.countStars() == 0)
		{
			field_.resetField();
			pacman_.setHealth(pacman_.getHealth() + 1);
			pacman_.respawn();
			redGhost_.respawn();
			pinkGhost_.respawn();
			blueGhost_.respawn();
			orangeGhost_.respawn();
			level_++;
		}
	}
}
