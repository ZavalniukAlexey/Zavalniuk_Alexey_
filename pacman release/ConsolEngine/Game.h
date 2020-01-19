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
		RedGhost rg_;
		PinkGhost pg_;
		BlueGhost bg_;
		OrangeGhost og_;
		int score = 0;
		int level_ = 0;
	public:
		Game();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};
