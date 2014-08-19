#include "Framework\timer.h"
#include "game.h"
#include "gameStage.h"
#include "maps.h"

struct Ghost
{
	int health;
	int damage;
	int speed;
	unsigned int x, y;
};

struct Pacman
{
	int health;
	int damage;
	int speed;
	unsigned int x, y;
};

void test();
void test2();