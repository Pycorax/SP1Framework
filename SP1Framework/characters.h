#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Framework\timer.h"
#include "game.h"
#include "gameStage.h"
#include "maps.h"
#include <Windows.h>

extern COORD charLocation;
extern enum direction;

struct Ghost
{
	int health;
	int speed;
	COORD coord;
	direction direct;
	short zoneID;

	Ghost(int healthPoints, int speedPoints, short givenZoneID, unsigned int coord_X, unsigned int coord_Y)
	{
		health = healthPoints;
		speed = speedPoints;
		//zoneID = givenZoneID;

		coord.X = coord_X;
		coord.Y = coord_Y;
	}

	void printGhost()
	{
		colour(FOREGROUND_BLUE | FOREGROUND_RED);
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT);
		cout << "/ \\";
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + 1);
		cout << "o-o";
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + 2);
		cout << "vvv";
	}
};

struct Pacman
{
	int health;
	int speed;
	int lives;
	COORD coord;

	Pacman()
	{
		health = 1;
		speed = 1;
		lives = 3;
		coord.X = charLocation.X;
		coord.Y = charLocation.Y;
	}

	bool isAlive()
	{
		if(lives < 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};

#endif