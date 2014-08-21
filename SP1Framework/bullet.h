#ifndef BULLET_H
#define BULLET_H

#include "Framework\timer.h"
#include "game.h"
#include "gameStage.h"
#include "maps.h"
#include "characters.h"

extern enum direction;
extern struct Map;
extern struct Pacman;

struct Bullet
{
	int damage;
	int speed;
	COORD coord;
	COORD oldCoord;
	direction direct;
	bool collided;

	Bullet(Pacman player);
	void draw();
	void undraw(Map currentMap);
	void move(Map currentMap);
};

#endif