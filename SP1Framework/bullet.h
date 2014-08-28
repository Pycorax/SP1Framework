#ifndef BULLET_H
#define BULLET_H

#include "maps.h"
#include "characters.h"

extern enum DIRECTION;
extern struct Map;
extern struct Pacman;

struct Bullet
{
	int damage;
	int speed;
	COORD coord;
	COORD oldCoord;
	DIRECTION direct;
	bool collided;
	bool firstMove;

	Bullet(Pacman player, int bulletDamage,int bulletSpeed);
	void draw();
	void undraw(Map currentMap);
	bool move(Map currentMap);
};

#endif