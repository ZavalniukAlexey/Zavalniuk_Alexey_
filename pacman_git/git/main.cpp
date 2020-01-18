
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
	RedGhost red(18, 8, 1, 'R');
	PinkGhost pink(19, 8, 1, 'P');
	BlueGhost blue(20, 8,1,'B');
	OrangeGhost orange(21,8,1,'O');
	Field field;
	Game app(pacman, red, pink, blue, orange, field);
	app.run(app);
}

