#pragma once

#include "BaseApp.hpp"
#include "BlueGhost.hpp"
#include "RedGhost.hpp"
#include "PinkGhost.hpp"
#include "OrangeGhost.hpp"
#include "Pacman.hpp"
#include "Field.hpp"

class Game : public BaseApp
{
private:
	Pacman pacman_;
	RedGhost red_;
	PinkGhost pink_;
	BlueGhost blue_;
	OrangeGhost orange_;
	Field field_;
	typedef BaseApp Parent;

	private:
	public:
		Game();
		Game(Pacman pacman, RedGhost red, PinkGhost pink, BlueGhost blue, OrangeGhost orange, Field field);
		
		int getX()const;
		int getY()const;

		Pacman getPacman() { return pacman_; }
		RedGhost getRedghost() { return red_; }	
		PinkGhost getPinkghost() { return pink_; }	
		BlueGhost getBlueghost() { return blue_; }	
		OrangeGhost getOrangeghost() { return orange_; }
		Field getField() { return field_; }
		void setPacman(Pacman p);
		void setRed(RedGhost r);
		void setPink(PinkGhost p);
		void setBlue(BlueGhost b);
		void setOrange(OrangeGhost o);
		void setField(Field F);
		virtual void keyPressed(Pacman &pacman, int btnCode, Field &field);
		virtual void play(float deltaTime);
};
