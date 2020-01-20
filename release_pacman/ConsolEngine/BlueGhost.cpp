#include "BlueGhost.h"




BlueGhost::BlueGhost() {
	posXOld_ = startingX_ = posX_ = 14;
	posYOld_ = startingY_ = posY_ = 15;
	health_ = 1;
	displayName_ = 'B';
	frighten_ = false;
	chase_ = true;
	direction_ = 'l';
}
BlueGhost::BlueGhost(const int x, const int y, const int hp, const char name) {
	posX_ = x;
	posY_ = y;
	posXOld_ = x;
	posYOld_ = y;
	health_ = hp;
	displayName_ = name;
	startingY_ = y;
	startingX_ = x;
	frighten_ = false;
	chase_ = true;
	direction_ = 'l';
}

void BlueGhost::move(const int xPacman, const int yPacman, const int xRed, const int yRed, Field field) {
	moveToPoint(2 * xRed - xPacman, 2 * yRed - yPacman, field);
}

BlueGhost::~BlueGhost() {
}
