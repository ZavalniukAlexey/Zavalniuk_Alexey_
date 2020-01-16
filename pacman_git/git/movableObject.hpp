#pragma once
class movableObject
{
protected:
	int posX_;
	int posY_;
	int posXOld_;
	int posYOld_;
	int health_;
	char displayName_;
	int startingX_;
	int startingY_;
	char direction_;
public:
	movableObject();
	movableObject(const int x, const int y, const int hp, const char c);
	char getDisplayName() const;
	int getX()const;
	int getY()const;
	int getStartingX()const;
	int getStartingY()const;
	void setX(const int x);
	void setY(const  int y);
	int getXOld()const;
	int getYOld()const;
	void setXOld(const int x);
	void setYOld(const  int y);
	void setDirection(const char c);
	int getHealth()const;
	virtual ~movableObject();
};
