#include "characters.h"

Ghost::Ghost(int healthPoints, int speedPoints, short givenZoneID)
{
	health = healthPoints;
	speed = speedPoints;
	zoneID = givenZoneID + 48;	
		
	srand(time(NULL));

	coord.X = rand() % 3 + 1;
	coord.Y = rand() % 3 + 1;

	oldCoord = coord;
}

void Ghost::printGhost()
{
	colour(FOREGROUND_BLUE | FOREGROUND_RED);
	gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET);
	cout << "/ \\";
	gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET + 1);
	cout << "o-o";
	gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET + 2);
	cout << "vvv";
}

void Ghost::move(vector<vector<char>> processedAIMap)
{
	static short changeX = 0;
	static short changeY = -1;

	if(!(processedAIMap[coord.X + changeX][coord.Y + changeY] == zoneID))
	{

		if(processedAIMap[coord.X][coord.Y - speed] == zoneID) //Up
		{
			changeX = 0;
			changeY = -speed;
		}

		if (processedAIMap[coord.X - speed][coord.Y] == zoneID) // Left
		{ 
			changeX = -speed;
			changeY = 0;
		}
		
		if (processedAIMap[coord.X][coord.Y + speed] == zoneID)//Down
		{
			changeX = 0;
			changeY = +speed;
		}

		if(processedAIMap[coord.X + speed][coord.Y] == zoneID) //Right
		{ 
			changeX = speed;
			changeY = 0;
		} 
	}
	
	if(!(processedAIMap[coord.X + changeX][coord.Y + changeY] == processedAIMap[coord.X - speed][coord.Y]))
	{
		if(processedAIMap[coord.X][coord.Y - speed] == zoneID) //Up
		{
			changeX = 0;
			changeY = -speed;
		}
	}

	oldCoord = coord;
	
	coord.X += changeX;
	coord.Y += changeY;

}

Pacman::Pacman()
{
	health = 1;
	speed = 1;
	lives = 3;
	coord.X = charLocation.X;
	coord.Y = charLocation.Y;
}

bool Pacman::isAlive()
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