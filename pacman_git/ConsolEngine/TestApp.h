#pragma once

#include "BaseApp.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
	public:
		TestApp();
		virtual void keyPressed(int btnCode);
		virtual void play(float deltaTime);
};
