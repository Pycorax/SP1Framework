#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Framework\timer.h"
#include "game.h"
#include "gameStage.h"
#include "maps.h"
#include <Windows.h>
#include <ctime>
#include <vector>
#include "bullet.h"

using std::time;
using std::vector;

extern enum direction;
extern struct Map;
extern struct Bullet;
extern struct ZoneBounds;

struct Ghost
{
	int health;
	int speed;
	COORD coord;
	COORD oldCoord;
	COORD change;
	bool wasVertical;
	direction direct;
	char zoneID;
	int damage;

	Ghost(int healthPoints, int speedPoints, short givenZoneID, ZoneBounds zoneCoords);
	void draw();
	void undraw(Map currentMap);
	void move(Map currentMap, bool clockwise = true);
	bool isHitByBullet(Bullet shot);
	bool Ghost::isAlive();
};

struct Pacman
{
	int health;
	int speed;
	int lives;
	COORD coord;
	COORD oldCoord;
	direction direct;

	Pacman(Map currentMap);
	void move(Map currentMap);
	void draw();
	void undraw(Map currentMap);
	bool isAlive();
	bool isHitByGhost(Ghost enemy);
};

#endif