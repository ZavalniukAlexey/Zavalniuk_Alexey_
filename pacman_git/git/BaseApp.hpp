#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "Pacman.hpp"
#include "Ghost.hpp"

class Game;
class BaseApp
{
private:
	HANDLE mConsole;
	HANDLE mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;
	void Render();

public:

	const int X_SIZE;
	const int Y_SIZE;

	BaseApp(int xSize=100, int ySize=80);
	virtual ~BaseApp();
	//void run()
	void run(Game game);
	void setChar(const int x, const int y, const wchar_t c);
	wchar_t getChar(const int x, const int y);
	virtual void play(float deltaTime);
	virtual void keyPressed(Pacman &pacman, int btnCode, Field &field);
};