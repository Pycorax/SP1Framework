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

	Ghost(int healthPoints, int speedPoints, short givenZoneID)
	{
		health = healthPoints;
		speed = speedPoints;
		zoneID = givenZoneID + 48;
		

		//TODO: 
		//Rand not wokring seemingly
	
		coord.X = 2;

		
		coord.Y = 2;
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

	void move(vector<vector<char>> processedAIMap)
	{
		/*for(int i = 0; i > coord.X && i > coord.Y; --i)
		{
			if(coord.X > 0 && coord.Y > 0)
			{
				++coord.X;
			}

			else
			{
				++coord.Y;
			}
		}*/

		static short changeX = 0;
		static short changeY = 1;

		if(!(processedAIMap[coord.X + changeX][coord.Y + changeY] == zoneID))
		{
			if(processedAIMap[coord.X][coord.Y - speed] == zoneID) //Up
			{
				changeY = -speed;
				
			}
			else if(processedAIMap[coord.X + speed][coord.Y] == zoneID) //Right
			{
				changeX = speed;
			}
		}
		
		coord.X += changeX;
		coord.Y += changeY;

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