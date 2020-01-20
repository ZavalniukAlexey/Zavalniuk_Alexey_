#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class BaseApp
{
public:
	bool endGame_ = false;
	const int X_SIZE_;
	const int Y_SIZE_;

	BaseApp(int xSize, int ySize);
	virtual ~BaseApp();
	void setChar(int x, int y, wchar_t c);
	void run();
	wchar_t getChar(int x, int y);
	virtual void updateF (float deltaTime){}
	virtual void keyPressed (int btnCode){}
private:
	HANDLE mConsole_;
	HANDLE mConsoleIn_;
	CHAR_INFO* mChiBuffer_;
	COORD mDwBufferSize_;
	COORD mDwBufferCoord_;
	SMALL_RECT mLpWriteRegion_;
	void Render();

};