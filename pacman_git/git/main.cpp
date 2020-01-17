
#include "Game.hpp"
#include "BlueGhost.hpp"
#include "RedGhost.hpp"
#include "PinkGhost.hpp"
#include "OrangeGhost.hpp"
#include "Pacman.hpp"
#include "Field.hpp"
void main()
{
	Pacman pacman(2, 23, 3, '@');
	RedGhost red(6, 20, 1, 'R');
	PinkGhost pink(21, 6, 1, 'P');
	BlueGhost blue(22, 6,1,'B');
	OrangeGhost orange(23,6,1,'O');
	Field field;
	Game app(pacman, red, pink, blue, orange, field);
	app.run(app);
}

