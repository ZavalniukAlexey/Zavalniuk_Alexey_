#pragma once
#include "Pacman.h"
#include "Ghost.h"
#include "RedGhost.h"
#include "PinkGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "Field.h"
#include "BaseApp.h"
#include <memory>
#include <vector>

class Game : public BaseApp
{
	typedef BaseApp Parent;

public:
	Game();
	virtual void keyPressed(int btnCode);
	virtual void updateF(float deltaTime);
	void scareGhosts();
	void scatterGhosts();
	void setScareCounter(const int num);
	int getScareCounter();
private:
	Pacman pacman_;
	Field field_;
	RedGhost redGhost_;
	PinkGhost pinkGhost_;
	BlueGhost blueGhost_;
	OrangeGhost orangeGhost_;
	//std::vector<std::shared_ptr<Ghost>> ghosts_;
	int score_ = 0;
	int level_ = 0;
	int speed_ = 0;
	int step_ = 7;
	int maxSpeed_ = 64;
	int ghostScore_ = 0;
	int scareCounter_ = 0;
};
