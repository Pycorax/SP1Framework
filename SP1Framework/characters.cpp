#include "characters.h"

COORD ghostLocation;

void test()
{
	Ghost ghost;
	Ghost Ghost1;
	Ghost Ghost2;

	ghost.speed = 10;
	Ghost1.speed = 20;
	Ghost2.speed = 30;

	ghost.health = 1;
	Ghost1.health = 2;
	Ghost2.health = 3;

	ghost.damage = 1;
	Ghost1.damage = 1;
	Ghost2.damage = 1;

	ghost.x = 0;
	ghost.y = 0;

	Ghost1.x = 10;
	Ghost1.y = 10;

	Ghost2.x = 10;
	Ghost2.y = 10;
}

void test2()
{
	Pacman pacman;

	pacman.health = 1;
	pacman.damage = 1;
	pacman.speed = 2;

	pacman.x = 0;
	pacman.y = 0;
}

