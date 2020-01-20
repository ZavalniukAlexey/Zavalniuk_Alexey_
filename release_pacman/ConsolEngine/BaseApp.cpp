
#include "Game.h"
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>
#include "Consts.h"
#define MY_PERFORMENCE_COUNTER

#include "PerformanceCounter.h"

BaseApp::BaseApp(int xSize, int ySize) : X_SIZE_(xSize), Y_SIZE_(ySize){
	SMALL_RECT windowSize = {0, 0, X_SIZE_, Y_SIZE_};
	COORD windowBufSize = {X_SIZE_+1, Y_SIZE_+1};

	mConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn_ = GetStdHandle(STD_INPUT_HANDLE);

	if(!SetConsoleScreenBufferSize(mConsole_,  windowBufSize))	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
	}
	if(!SetConsoleWindowInfo(mConsole_, TRUE, &windowSize))	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole_, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole_, &cursorInfo);


	mChiBuffer_ = (CHAR_INFO*)malloc((X_SIZE_+1)*(Y_SIZE_+1)*sizeof(CHAR_INFO));

	mDwBufferSize_.X = X_SIZE_ + 1;
	mDwBufferSize_.Y = Y_SIZE_ + 1;		

	mDwBufferCoord_.X = 0;
	mDwBufferCoord_.Y = 0;				

	mLpWriteRegion_.Left = 0;
	mLpWriteRegion_.Top = 0;
	mLpWriteRegion_.Right = X_SIZE_ + 1;
	mLpWriteRegion_.Bottom = Y_SIZE_ + 1;	


	for (int x=0; x<X_SIZE_+1; x++) {
		for (int y=0; y<Y_SIZE_+1; y++) {
			setChar(x, y, L' ');
		}
	}
}

BaseApp::~BaseApp() {

}

void BaseApp::setChar(int x, int y, wchar_t c) {
	mChiBuffer_[x + (X_SIZE_+1)*y].Char.UnicodeChar = c;
	mChiBuffer_[x + (X_SIZE_+1)*y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;

}

wchar_t BaseApp::getChar(int x, int y) {
	return mChiBuffer_[x + (X_SIZE_+1)*y].Char.AsciiChar;
}

void BaseApp::Render() {
	if (!WriteConsoleOutput(mConsole_, mChiBuffer_, mDwBufferSize_, mDwBufferCoord_, &mLpWriteRegion_)) 
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError()); 
	}
}

void BaseApp::run() {
	CStopwatch timer;
	int sum = 0;
	int counter = 0;
	int btnCode = 0;
	int deltaTime = 0;
	while (1)
	{
		timer.start();
		if (kbhit())
		{
			btnCode = getch();
			if (!FlushConsoleInputBuffer(mConsoleIn_))
				cout<<"FlushConsoleInputBuffer failed with error "<<GetLastError();
		}
		if (btnCode == getIgnoredNumber())
			continue;
		keyPressed(btnCode);
		updateF((float)deltaTime / getThousandFloat());
		if (endGame_)
		{
			this->~BaseApp();
			return;
		}
		Render();

		while (true) {
			deltaTime = timer.now();
			if (deltaTime > 20)
				break;
		}

		sum += deltaTime;
		counter++;
		if (sum >= getThousand()) {
			const int size = 255;
			TCHAR  szbuff[size];
			StringCchPrintf(szbuff, size, TEXT("FPS: %d"), counter);
			SetConsoleTitle(szbuff);

			counter = 0;
			sum = 0;
		}
	}
}