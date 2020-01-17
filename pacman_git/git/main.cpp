
#include "Game.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "Field.hpp"
void main ()
{
	Field field;
	Pacman pacman(2,29,3,'@');
	Ghost red(12,11,1, 'r');
	Ghost pink(13,11,1, 'p');
	Ghost blue(14,11,1, 'b');
	Ghost orange(15,11,1, 'o');
	Game app;
	app.run(pacman, red, pink, blue, orange, field);
}

