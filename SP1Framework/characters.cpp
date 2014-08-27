#include "characters.h"
#include <ctime>
#include "Framework\console.h"
#include <iostream>
#include "scorePoints.h"

using std::cout;

Ghost::Ghost(short healthPoints, short speedPoints, unsigned short givenZoneID, unsigned short respawn, Map &currentMap)
{
	maxHealth = healthPoints;
	health = maxHealth;
	speed = speedPoints;
	numericZoneID = givenZoneID;
	zoneID = numericZoneID + 48;
	damage = 1;
	timeToRespawn = respawn;

	change.X = 0;
	change.Y = -1;
	wasVertical = true;
	
	do 
	{
		srand(time(NULL));
		coord.X = rand() % (currentMap.zoneCoords[numericZoneID].maxX - currentMap.zoneCoords[numericZoneID].minX + 1) + currentMap.zoneCoords[numericZoneID].minX;
		coord.Y = rand() % (currentMap.zoneCoords[numericZoneID].maxY - currentMap.zoneCoords[numericZoneID].minY + 1) + currentMap.zoneCoords[numericZoneID].minY;
	}
	while (currentMap.processedAIMap[coord.Y][coord.X] != zoneID);

	oldCoord = coord;
}

void Ghost::draw()
{
	static bool even = true;

	colour(FOREGROUND_BLUE | FOREGROUND_RED);

	if(even)
	{
		gotoXYTile(coord.X, coord.Y);
		cout << "/ \\";
		gotoXYTileDown(coord, 1);
		cout << "o-o";
		gotoXYTileDown(coord, 2);
		cout << "vvv";

		even = false;
	}
	else
	{
		gotoXYTile(coord.X, coord.Y);
		cout << "/ \\";
		gotoXYTileDown(coord, 1);
		cout << "o-o";
		gotoXYTileDown(coord, 2);
		cout << "VVV";

		even = true;
	}
}

void Ghost::undraw(Map &currentMap)
{
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord);
}

void Ghost::move(Map &currentMap, bool clockwise)
{
	if(currentMap.processedAIMap[coord.Y + change.Y][coord.X + change.X] != zoneID)
	{
		if(wasVertical)
		{
			if(clockwise)
			{
				if(currentMap.processedAIMap[coord.Y][coord.X + speed] == zoneID) //Right
				{ 
					change.X = speed;
					change.Y = 0;
					wasVertical = false;
				}
				else if (currentMap.processedAIMap[coord.Y][coord.X - speed] == zoneID) // Left
				{ 
					change.X = -speed;
					change.Y = 0;
					wasVertical = false;
				}
				else
				{
					if (currentMap.processedAIMap[coord.Y + speed][coord.X] == zoneID)//Down
					{
						change.X = 0;
						change.Y = speed;
						wasVertical = true;
					}
					else if(currentMap.processedAIMap[coord.Y - speed][coord.X] == zoneID) //Up
					{
						change.X = 0;
						change.Y = -speed;
						wasVertical = true;
					}
				}

			}
			else
			{
				if (currentMap.processedAIMap[coord.Y][coord.X - speed] == zoneID) // Left
				{ 
					change.X = -speed;
					change.Y = 0;
					wasVertical = false;
				}
				else if(currentMap.processedAIMap[coord.Y][coord.X + speed] == zoneID) //Right
				{ 
					change.X = speed;
					change.Y = 0;
					wasVertical = false;
				}
				else
				{
					if(currentMap.processedAIMap[coord.Y - speed][coord.X] == zoneID) //Up
					{
						change.X = 0;
						change.Y = -speed;
						wasVertical = true;
					}
					else if (currentMap.processedAIMap[coord.Y + speed][coord.X] == zoneID)//Down
					{
						change.X = 0;
						change.Y = speed;
						wasVertical = true;
					}
				}
			}
			
		}
		else
		{
			if(clockwise)
			{
				if (currentMap.processedAIMap[coord.Y + speed][coord.X] == zoneID)//Down
				{
					change.X = 0;
					change.Y = speed;
					wasVertical = true;
				}
				else if(currentMap.processedAIMap[coord.Y - speed][coord.X] == zoneID) //Up
				{
					change.X = 0;
					change.Y = -speed;
					wasVertical = true;
				}
				else
				{
					if(currentMap.processedAIMap[coord.Y][coord.X + speed] == zoneID) //Right
					{ 
						change.X = speed;
						change.Y = 0;
						wasVertical = false;
					}
					else if (currentMap.processedAIMap[coord.Y][coord.X - speed] == zoneID) // Left
					{ 
						change.X = -speed;
						change.Y = 0;
						wasVertical = false;
					}
				}

			}
			else
			{
				if(currentMap.processedAIMap[coord.Y - speed][coord.X] == zoneID) //Up
				{
					change.X = 0;
					change.Y = -speed;
					wasVertical = true;
				}
				else if (currentMap.processedAIMap[coord.Y + speed][coord.X] == zoneID)//Down
				{
					change.X = 0;
					change.Y = speed;
					wasVertical = true;
				}
				else
				{
					if (currentMap.processedAIMap[coord.Y][coord.X - speed] == zoneID) // Left
					{ 
						change.X = -speed;
						change.Y = 0;
						wasVertical = false;
					}
					else if(currentMap.processedAIMap[coord.Y][coord.X + speed] == zoneID) //Right
					{ 
						change.X = speed;
						change.Y = 0;
						wasVertical = false;
					}
				}
			}
		}
	}

	//Prevents oldCoord from being changed if the ghost did not move at all
	if (change.X != 0 || change.Y != 0)
	{
		oldCoord = coord;
	}

	coord.X += change.X;
	coord.Y += change.Y;
}

bool Ghost::isHitByBullet(Bullet shot, Map &currentMap)
{
	if((shot.oldCoord.X == coord.X && shot.oldCoord.Y == coord.Y) || (shot.coord.X == coord.X && shot.coord.Y == coord.Y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Ghost::isAlive()
{
	if(health < 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Ghost::respawn(Map &currentMap)
{
	if(!isAlive())
	{
			srand(time(NULL));
			coord.X = rand() % (currentMap.zoneCoords[numericZoneID].maxX - currentMap.zoneCoords[numericZoneID].minX + 1) + currentMap.zoneCoords[numericZoneID].minX;
			coord.Y = rand() % (currentMap.zoneCoords[numericZoneID].maxY - currentMap.zoneCoords[numericZoneID].minY + 1) + currentMap.zoneCoords[numericZoneID].minY;
		if (currentMap.processedAIMap[coord.Y][coord.X] == zoneID)
		{
			oldCoord = coord;

			health = maxHealth;

			change.X = 0;
			change.Y = -1;
			wasVertical = true;
		}
	}
}

Pacman::Pacman(Map &currentMap)
{
	health = 1;
	speed = 1;
	lives = 3;
	coord.X = currentMap.startPos.X;
	coord.Y = currentMap.startPos.Y;
	oldCoord = coord;
	direct = E_RIGHT_DIRECTION;
}

void Pacman::move(Map &currentMap)
{
	switch(direct)
	{
		case E_UP_DIRECTION:
			if(currentMap.processedMap[coord.Y - speed][coord.X] != '#')
			{
				coord.Y -= speed;
			}
			break;
		case E_DOWN_DIRECTION:
			if(currentMap.processedMap[coord.Y + speed][coord.X] != '#')
			{
				coord.Y += speed;
			}
			break;
		case E_LEFT_DIRECTION:
			if(currentMap.processedMap[coord.Y][coord.X - speed] != '#')
			{
				coord.X -= speed;
			}
			break;
		case E_RIGHT_DIRECTION:
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
		case E_UP_DIRECTION:
			if(even)
			{
				gotoXYTile(coord);
				cout << "\\/";
				gotoXYTileDown(coord, 1);
				cout << "||";
				gotoXYTileDown(coord, 2);
				cout << "~*";
				even = false;
			}
			else
			{
				gotoXYTile(coord);
				cout << "|";
				gotoXYTileDown(coord, 1);
				cout << "||";
				gotoXYTileDown(coord, 2);
				cout << "~*";
				even = true;
			}
				
			break;

		case E_DOWN_DIRECTION:	
			if(even)
			{
				gotoXYTile(coord);
				cout << "~*";
				gotoXYTileDown(coord, 1);
				cout << "||";
				gotoXYTileDown(coord, 2);
				cout << "/\\";
				even = false;
			}
			else
			{
				gotoXYTile(coord);
				cout << "~*";
				gotoXYTileDown(coord, 1);
				cout << "||";
				gotoXYTileDown(coord, 2);
				cout << "|";
				even = true;
			}
				 
			break;

		case E_LEFT_DIRECTION:
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

		case E_RIGHT_DIRECTION:	
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

void Pacman::undraw(Map &currentMap)
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

bool Pacman::isHitByGhost(Ghost enemy)
{
	if(coord.X == enemy.oldCoord.X && coord.Y == enemy.oldCoord.Y)
	{
		Beep(200, 100);
		return true;
	}
	else
	{
		return false;
	}
}