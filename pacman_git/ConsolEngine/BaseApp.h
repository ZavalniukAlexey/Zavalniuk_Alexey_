#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

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
	//������� ������� ������ �� ����������� � ��������� � ��������
	const int X_SIZE;
	const int Y_SIZE;

	//����������� �������� ������� ������� ������ �� ����������� � ��������� � ��������
	BaseApp(int xSize=100, int ySize=80);
	virtual ~BaseApp();

	//��������� ������� ����
	void run();

	//����� ��������� x,y-������ ������ ������������ ��������, ��� ������� ���
	void setChar(int x, int y, wchar_t c);
	wchar_t getChar(int x, int y);

	/*��� ������� ���������� ������ ������� ��������, � ����� ��������������, � ���������� ������.
	� �� �������� deltaTime - ������� �� ������� ����� ���������� ��������� � ����, � ��������*/
	virtual void play (float deltaTime){}
	/*��� ������� ���������� ��� ������� ������� �� ����������, � �� �������� ��� ������� - btnCode.
	���� ������������ ������� ��� �������������� �������, �� ������ ����� ��� ��� �����, �������� 224, � ��������� �� ��� - 
	����� ��� ��������������� ��� ����� �������, ��� ����� ��������, ������ ����� getch().
	����� keyPressed ��� �� ����� �������������� � ����������*/
	virtual void keyPressed (int btnCode){}
};