#pragma once
#include "Pacman.h"
#include "RedGhost.h"
#include "PinkGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "Field.h"
#include "BaseApp.h"

class Game : public BaseApp
{
	typedef BaseApp Parent;

	private:
		Pacman pacman_;
		Field field_;
		RedGhost redGhost_;
		PinkGhost pinkGhost_;
		BlueGhost blueGhost_;
		OrangeGhost orangeGhost_;
		int score_ = 0;
		int level_ = 0;
		int speed_ = 0;
		int step_ = 10;
		int maxSpeed_ = 80;
	public:
		Game();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};
