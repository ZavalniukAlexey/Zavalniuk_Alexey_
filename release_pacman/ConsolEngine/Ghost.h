#pragma once
#include "MovableObject.h"
#include "Field.h"
#include <memory>

/*class RedGhost;
class PinkGhost;
class BlueGhost;
class OrangeGhost;*/

class Ghost :
	public MovableObject
{

public:
	Ghost();
	Ghost(const int x, const  int y, const  int hp, const  char c);
	virtual ~Ghost();

	void respawn();
	void moveToPoint(const int x, const int y, const Field F);
	void chooseDirection(const double top, const double bot, const double left, const double right);
	void turn(const Field field, const int xPacman, const int yPacman);
	static std::shared_ptr<Ghost> createGhosts(char type);
	virtual void move(const int xPacman, const int yPacman, const Field F);
	//virtual void move(const int xPacman, const int yPacman, const char dirPacman, Field filed);
	//virtual void move(const int xPacman, const int yPacman, const int xRed, const int yRed, Field field);
	void setScare(bool state);
	bool getScare();
	void setScatter(bool state);
	bool getScatter();

protected:
	bool frighten_ = false;
	bool scatter_ = true;
	bool chase_ = true;
};

