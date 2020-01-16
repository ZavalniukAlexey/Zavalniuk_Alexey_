#pragma once

#include "BaseApp.hpp"
#include "Ghost.hpp"
#include "Pacman.hpp"
#include "Field.hpp"

class Game : public BaseApp
{
	typedef BaseApp Parent;

	private:
	public:
		Game();
		int getX()const;
		int getY()const;
		void keyPressed(Pacman &pacman, int btnCode, Field &field);
		void play(float deltaTime, Pacman &pacman, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange, Field &field);
};
