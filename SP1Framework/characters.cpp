#include "characters.h"

Ghost::Ghost(int healthPoints, int speedPoints, short givenZoneID)
{
	health = healthPoints;
	speed = speedPoints;
	zoneID = givenZoneID + 48;	
		
	srand(time(NULL));

	coord.X = rand() % 6 + 1;
	coord.Y = rand() % 6 + 1;

	oldCoord = coord;
}

void Ghost::draw()
{
	static bool even = true;

	colour(FOREGROUND_BLUE | FOREGROUND_RED);

	if(even)
	{
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET);
		cout << "/ \\";
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET + 1);
		cout << "o-o";
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET + 2);
		cout << "vvv";

		even = false;
	}
	else
	{
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET);
		cout << "/ \\";
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET + 1);
		cout << "o-o";
		gotoXY(coord.X * TILE_WIDTH, coord.Y * TILE_HEIGHT + HUD_OFFSET + 2);
		cout << "VVV";

		even = true;
	}
}

void Ghost::undraw(Map currentMap)
{
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord);
}

void Ghost::move(Map currentMap)
{
	static short changeX = 0;
	static short changeY = -1;

	if(!(currentMap.processedAIMap[coord.X + changeX][coord.Y + changeY] == zoneID))
	{
		oldCoord = coord;
		if(currentMap.processedAIMap[coord.X][coord.Y - speed] == zoneID) //Up
		{
			changeX = 0;
			changeY = -speed;
		}
		else if(currentMap.processedAIMap[coord.X + speed][coord.Y] == zoneID) //Right
		{ 
			changeX = speed;
			changeY = 0;
		} 

		else if (currentMap.processedAIMap[coord.X - speed][coord.Y] == zoneID) // Left
		{ 
			changeX = -speed;
			changeY = 0;
		}  

		else if (currentMap.processedAIMap[coord.X][coord.Y + speed] == zoneID)//Down
		{
			changeX = 0;
			changeY = +speed;
		}
	}

	oldCoord = coord;
	
	coord.X += changeX;
	coord.Y += changeY;

}

bool Ghost::isHitByBullet(Bullet shot)
{
	if(shot.coord.X == coord.X && shot.coord.Y == coord.Y)
	{
		health -= shot.damage;
		return true;
	}
	else
	{
		return false;
	}
}

Pacman::Pacman(Map currentMap)
{
	health = 1;
	speed = 1;
	lives = 3;
	coord.X = currentMap.startPos.X;
	coord.Y = currentMap.startPos.Y;
	oldCoord = coord;
	direct = RIGHT;
}

void Pacman::move(Map currentMap)
{
	switch(direct)
	{
		case UP:
			if(currentMap.processedMap[coord.Y - speed][coord.X] != '#')
			{
				coord.Y -= speed;
			}
			break;
		case DOWN:
			if(currentMap.processedMap[coord.Y + speed][coord.X] != '#')
			{
				coord.Y += speed;
			}
			break;
		case LEFT:
			if(currentMap.processedMap[coord.Y][coord.X - speed] != '#')
			{
				coord.X -= speed;
			}
			break;
		case RIGHT:
			if(currentMap.processedMap[coord.Y][coord.X + speed] != '#')
			{
				coord.X += speed;
			}
			break;
	}
}

void Pacman::draw()
{
	static bool even = true;
	switch(direct)
	{
		case UP:
			if(even)
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "(*<";
				even = false;
			}
			else
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "(*=";
				even = true;
			}
				
			break;

		case DOWN:	
			if(even)
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "(*<";
				even = false;
			}
			else
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "(*=";
				even = true;
			}
				 
			break;

		case LEFT:
			if(even)
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << ">*)";
				even = false;
			}
			else
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "=*)";
				even = true;
			}
				 
			break;

		case RIGHT:	
			if(even)
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "(*<";
				even = false;
			}
			else
			{
				gotoXYTile(coord);
				cout << "___";
				gotoXYTileDown(coord, 1);
				cout << "(*=";
				even = true;
			}
				 
			break;
	}
}

void Pacman::undraw(Map currentMap)
{
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord);
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