#include "Game.h"
#include "Consts.h"
#include "Ghost.h"
#include <vector>
Game::Game() : Parent(setFieldY()-2, setFieldX()-2) {
	/*ghosts_.reserve(4);
	ghosts_.push_back(Ghost::createGhosts('R'));
					 ^ factory error.png
					 same in 3 other pushbacks
					 factoryError.png included in git
	ghosts_.push_back(Ghost::createGhosts('P'));
	ghosts_.push_back(Ghost::createGhosts('B'));
	ghosts_.push_back(Ghost::createGhosts('O'));*/

}

void Game::keyPressed(int btnCode) {
	
	char s = field_.getFieldChar(pacman_.getX() - 1, pacman_.getY());

	if ((btnCode == getWCode() || btnCode == getUpCode()) && 
		field_.getFieldChar(pacman_.getX() - 1, pacman_.getY()) != '#') {
		pacman_.setDirection('t');
	}
	else if ((btnCode == getSCode() || btnCode == getDownCode()) && 
		field_.getFieldChar(pacman_.getX() + 1, pacman_.getY()) != '#') {
		pacman_.setDirection('b');
	}
	else if ((btnCode == getACode() || btnCode == getLeftCode()) && 
		field_.getFieldChar(pacman_.getX(), pacman_.getY() - 1) != '#') {
		pacman_.setDirection('l');
	}
	else if ((btnCode == getDCode() || btnCode == getRightCode()) && 
		field_.getFieldChar(pacman_.getX(), pacman_.getY() + 1) != '#') {
		pacman_.setDirection('r');
	}
}

void fixOutput(Game g, int score, int level) {
	int ScoreSize = 0;
	const int bufSize = 10;
	while (score /= 10)
	{
		ScoreSize++;
	}
	for (int i = 0; i < bufSize - ScoreSize; i++)
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

void drawField(Game g,
	const int score,
	const int ghostScore,
	const int hp,
	const int lvl,
	Field f) {
	const int bufSize = 10;
	for (int i = 0; i < setFieldX() - 1; i++)
		for (int j = 0; j < setFieldY() - 1; j++)
			g.setChar(j, i, f.getFieldChar(i, j));
	char bufScore[bufSize];
	char bufHealth[bufSize];
	char bufLevel[bufSize];
	sprintf_s(bufScore, "%d", score+ ghostScore);
	sprintf_s(bufHealth, "%d", hp-1);
	sprintf_s(bufLevel, "%d", lvl);

	for (int i = 0; i < bufSize; i++)
	{
		g.setChar(getScoreLength() + i, getScoreLine(), bufScore[i]);
		g.setChar(getHealthLength() + i, getHealthLine(), bufHealth[i]);
		g.setChar(getLevelLength() + i, getLevelLine(), bufLevel[i]);
	}

	fixOutput(g, score, lvl);
}

//bool collideObjects(Pacman &P, std::shared_ptr<Ghost> RG, std::shared_ptr<Ghost> PG, std::shared_ptr<Ghost> BG, std::shared_ptr<Ghost> OG )
bool collideObjects(Pacman &P, Ghost &G) {
	return ((P.getX() == G.getX() && P.getY() == G.getY()));
}
void respawn(Pacman &P,
	RedGhost &RG,
	PinkGhost &PG,
	BlueGhost &BG,
	OrangeGhost &OG,
	Game &g)
{
	RG.setScare(false);
	PG.setScare(false);
	BG.setScare(false);
	OG.setScare(false);
	P.respawn();
	RG.respawn();
	PG.respawn();
	BG.respawn();
	OG.respawn();
	g.setScareCounter(0);
}
//void moveObjects(Game &g, Pacman &P, std::shared_ptr<Ghost> RG, std::shared_ptr<Ghost> PG, std::shared_ptr<Ghost> BG, std::shared_ptr<Ghost> OG, Field &F, const int score)

void updateScore(Field &f,
	Pacman pacman,
	Game &game,
	int &score){
	if (f.getFieldChar(pacman.getX(), pacman.getY()) == '.') {
		score += 10;
	}
	else if (f.getFieldChar(pacman.getX(), pacman.getY()) == 'a') {
		score += 10;
		game.scareGhosts();
		game.setScareCounter(1);
	}
}
void moveObjects(Game &g,
	Pacman &P,
	RedGhost &RG,
	PinkGhost &PG,
	BlueGhost &BG,
	OrangeGhost &OG,
	Field &F,
	int &score,
	int &ghostScore) {
	P.makeAStep(F);
	RG.move(P.getX(), P.getY(), F);
	g.setChar(RG.getY(), RG.getX(), RG.getDisplayName());

	PG.move(P.getX(), P.getY(), P.getDirection(), F);
	g.setChar(PG.getY(), PG.getX(), PG.getDisplayName());

	if (score%getMaxScore() > getScoreToSpawnBlue())
	{
		BG.move(P.getX(), P.getY(), RG.getX(), RG.getY(), F);
		g.setChar(BG.getY(), BG.getX(), BG.getDisplayName());
	}

	if (score%getMaxScore() > getStarsToSpawnOrange() * 10)	{
		OG.move(P.getX(), P.getY(), F);
		g.setChar(OG.getY(), OG.getX(), OG.getDisplayName());
	}
	updateScore(F, P, g, score);
	if (collideObjects(P, RG)) {
		if (RG.getScare())	{
			ghostScore += getGhostScoreBonus();
			RG.setScare(false);
			RG.respawn();
		}
		else {
			respawn(P, RG, PG, BG, OG, g);
		}
	}
	if (collideObjects(P, PG))	{
		if (PG.getScare())
		{
			ghostScore += getGhostScoreBonus();
			PG.setScare(false);
			PG.respawn();
		}
		else
		{
			respawn(P, RG, PG, BG, OG, g);
		}
	}
	if (collideObjects(P, BG))	{
		if (BG.getScare())
		{
			ghostScore += getGhostScoreBonus();
			BG.setScare(false);
			BG.respawn();
		}
		else {
			respawn(P, RG, PG, BG, OG, g);
		}
	}
	if (collideObjects(P, OG))	{
		if (OG.getScare())	{
			ghostScore += getGhostScoreBonus();
			OG.setScare(false);
			OG.respawn();
		}
		else {
			respawn(P, RG, PG, BG, OG, g);
		}
	}

	F.setFieldChar(P.getXOld(), P.getYOld(), ' ');
	F.setFieldChar(P.getX(), P.getY(), P.getDisplayName());
	P.setXOld(P.getX());
	P.setYOld(P.getY());
}
bool nextStep(int &speed, const int step, const int maxSpeed) {
	bool nextStep = false;
	speed += step;
	if (speed > maxSpeed) {
		speed %= maxSpeed;
		nextStep = true;
	}
	return nextStep;
}

void setStep(const int level, int &step) {
	if (level >= getSpeedUpLevelTwo())
		step = 9;
	else if (level >= getSpeedUpLevelOne())
		step = 8;
}

void Game::updateF(float deltaTime) {
	
	setStep(level_, step_);
	if (nextStep(speed_, step_, maxSpeed_))
	{
		drawField(*this, score_, ghostScore_, pacman_.getHealth(), level_, field_);
		moveObjects(*this, pacman_, redGhost_, pinkGhost_, blueGhost_, orangeGhost_, field_, score_, ghostScore_);
			
		if (pacman_.getHealth() == 0) {
			this->~Game();
			return;
		}

		if (field_.countStars() == 0) {
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

void Game::scareGhosts() {
	redGhost_.setScare(true);
	pinkGhost_.setScare(true);
	blueGhost_.setScare(true);
	orangeGhost_.setScare(true);
	scareCounter_ = 0;
}

void Game::scatterGhosts() {
	redGhost_.setScatter(true);
	pinkGhost_.setScatter(true);
	blueGhost_.setScatter(true);
	orangeGhost_.setScatter(true);
}

void Game::setScareCounter(const int num) {
	scareCounter_ = num;
}

int Game::getScareCounter() {
	return scareCounter_;
}
