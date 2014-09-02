#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "maps.h"
#include "bullet.h"
#include "options.h"

extern "C"
{
	enum DIRECTION;
	struct Map;
	struct Bullet;
	struct ZoneBounds;
};

struct Ghost
{
	int health;
	int maxHealth;
	int speed;
	COORD coord;
	COORD oldCoord;
	COORD change;
	bool wasVertical;
	DIRECTION direct;
	char zoneID;
	int numericZoneID;
	int damage;
	unsigned int timeToRespawn; //The time needed before the Ghost can respawn
	time_t respawnTime; //Time when the Ghost will respawn

	//Constructor
	Ghost(short healthPoints, short speedPoints, unsigned short givenZoneID, unsigned short respawn, Map &currentMap);

	//Drawing
	void draw();
	void undraw(Map &currentMap);
	//Movement
	void move(Map &currentMap, bool clockwise = true);
	//Interaction
	bool isHitByBullet(Bullet shot, Map &currentMap); //Contains code for killing Ghost as well
	bool isAlive();
	void respawn(Map &currentMap);
};

struct Pacman
{
	int health;
	int speed;
	int lives;
	COORD coord;
	COORD oldCoord;
	DIRECTION direct;

	//Aesthetics
	COLOR color;

	Pacman(Map &currentMap, int playerLives, COLOR playerColour);
	void move(Map &currentMap);
	void draw();
	void undraw(Map &currentMap);
	bool isAlive();
	bool isHitByGhost(Ghost enemy);
};

#endif