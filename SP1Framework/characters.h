#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Framework\timer.h"
#include "game.h"
#include "gameStage.h"
#include "maps.h"
#include <Windows.h>
#include <ctime>
#include <vector>

using std::time;
using std::vector;

extern COORD charLocation;
extern enum direction;

struct Ghost
{
	int health;
	int speed;
	COORD coord;
	COORD oldCoord;
	direction direct;
	char zoneID;

	Ghost(int healthPoints, int speedPoints, short givenZoneID);
	void printGhost();
	void move(vector<vector<char>> processedAIMap);
	
};

struct Pacman
{
	int health;
	int speed;
	int lives;
	COORD coord;

	Pacman();
	bool isAlive();
};

#endif