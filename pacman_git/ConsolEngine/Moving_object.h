#pragma once
class Moving_object
{
protected:
	int PosX_;
	int PosY_;
	int PosXOld_;
	int PosYOld_;
	int health_;
	char displayName_;
	int startingX_;
	int startingY_;
	char direction_;
public:
	Moving_object();
	Moving_object(int x, int y, int hp, char c);
	char GetDisplayName();
	int GetX();
	int GetY();
	int GetStartingX();
	int GetStartingY();
	void SetX(int x);
	void SetY(int y);
	int GetXOld();
	int GetYOld();
	int GetHealth();
	virtual ~Moving_object();
};

