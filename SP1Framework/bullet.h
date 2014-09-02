#ifndef BULLET_H
#define BULLET_H

#include "maps.h"
#include "characters.h"
#include "options.h"

extern "C"
{
	enum DIRECTION;
	struct Map;
	struct Pacman;
};

struct Bullet
{
	int damage;
	int speed;
	COORD coord;
	COORD oldCoord;
	COORD change;
	DIRECTION direct;
	bool collided;
	bool firstMove;

	//Aesthetics
	COLOR color;

	Bullet(Pacman player, int bulletDamage,int bulletSpeed, COLOR bulletColor);
	void draw();
	void undraw(Map currentMap);
	bool move(Map currentMap);
};

#endif