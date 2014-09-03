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
		srand(static_cast<unsigned int>(time(NULL)));
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
		switch(health)
		{
			case 1:
				colour(FOREGROUND_GREEN);
				gotoXYTile(coord.X, coord.Y);
				cout << "/1\\";
				gotoXYTileDown(coord, 1);
				cout << "o-o";
				gotoXYTileDown(coord, 2);
				cout << "vvv";
				break;

			case 2:
				gotoXYTile(coord.X, coord.Y);
				cout << "/2\\";
				gotoXYTileDown(coord, 1);
				cout << "o-o";
				gotoXYTileDown(coord, 2);
				cout << "vvv";
				break;

			case 3:
				colour(FOREGROUND_RED);
				gotoXYTile(coord.X, coord.Y);
				cout << "[3]";
				gotoXYTileDown(coord, 1);
				cout << "O-O";
				gotoXYTileDown(coord, 2);
				cout << "vvv";
				break;
		}
		even = false;
	}
	else
	{
		switch(health)
		{
			case 1:
				colour(FOREGROUND_GREEN);
				gotoXYTile(coord.X, coord.Y);
				cout << "/1\\";
				gotoXYTileDown(coord, 1);
				cout << "o-o";
				gotoXYTileDown(coord, 2);
				cout << "VVV";
				break;

			case 2:
				gotoXYTile(coord.X, coord.Y);
				cout << "/2\\";
				gotoXYTileDown(coord, 1);
				cout << "o-o";
				gotoXYTileDown(coord, 2);
				cout << "VVV";
				break;

			case 3:
				colour(FOREGROUND_RED);
				gotoXYTile(coord.X, coord.Y);
				cout << "[3]";
				gotoXYTileDown(coord, 1);
				cout << "O-O";
				gotoXYTileDown(coord, 2);
				cout << "VVV";
				break;
		}
		even = true;
	}

}

void Ghost::undraw(Map &currentMap)
{
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord, currentMap.colors);
}

void Ghost::move(Map &currentMap, bool clockwise)
{
	bool oldCoordsNotSet = true;

	for (short turns = 0; turns < speed; ++turns)
	{
		if(currentMap.processedAIMap[coord.Y + change.Y][coord.X + change.X] != zoneID)
		{
			if(wasVertical)
			{
				if(clockwise)
				{
					if(currentMap.processedAIMap[coord.Y][coord.X + 1] == zoneID) //Right
					{ 
						change.X = 1;
						change.Y = 0;
						wasVertical = false;
					}
					else if (currentMap.processedAIMap[coord.Y][coord.X - 1] == zoneID) // Left
					{ 
						change.X = -1;
						change.Y = 0;
						wasVertical = false;
					}
					else
					{
						if (currentMap.processedAIMap[coord.Y +1][coord.X] == zoneID)//Down
						{
							change.X = 0;
							change.Y = 1;
							wasVertical = true;
						}
						else if(currentMap.processedAIMap[coord.Y - 1][coord.X] == zoneID) //Up
						{
							change.X = 0;
							change.Y = -1;
							wasVertical = true;
						}
					}

				}
				else
				{
					if (currentMap.processedAIMap[coord.Y][coord.X - 1] == zoneID) // Left
					{ 
						change.X = -1;
						change.Y = 0;
						wasVertical = false;
					}
					else if(currentMap.processedAIMap[coord.Y][coord.X + 1] == zoneID) //Right
					{ 
						change.X = 1;
						change.Y = 0;
						wasVertical = false;
					}
					else
					{
						if(currentMap.processedAIMap[coord.Y - 1][coord.X] == zoneID) //Up
						{
							change.X = 0;
							change.Y = -1;
							wasVertical = true;
						}
						else if (currentMap.processedAIMap[coord.Y + 1][coord.X] == zoneID)//Down
						{
							change.X = 0;
							change.Y = 1;
							wasVertical = true;
						}
					}
				}

			}
			else
			{
				if(clockwise)
				{
					if (currentMap.processedAIMap[coord.Y + 1][coord.X] == zoneID)//Down
					{
						change.X = 0;
						change.Y = 1;
						wasVertical = true;
					}
					else if(currentMap.processedAIMap[coord.Y - 1][coord.X] == zoneID) //Up
					{
						change.X = 0;
						change.Y = -1;
						wasVertical = true;
					}
					else
					{
						if(currentMap.processedAIMap[coord.Y][coord.X + 1] == zoneID) //Right
						{ 
							change.X = 1;
							change.Y = 0;
							wasVertical = false;
						}
						else if (currentMap.processedAIMap[coord.Y][coord.X - 1] == zoneID) // Left
						{ 
							change.X = -1;
							change.Y = 0;
							wasVertical = false;
						}
					}

				}
				else
				{
					if(currentMap.processedAIMap[coord.Y - 1][coord.X] == zoneID) //Up
					{
						change.X = 0;
						change.Y = -1;
						wasVertical = true;
					}
					else if (currentMap.processedAIMap[coord.Y + 1][coord.X] == zoneID)//Down
					{
						change.X = 0;
						change.Y = 1;
						wasVertical = true;
					}
					else
					{
						if (currentMap.processedAIMap[coord.Y][coord.X - 1] == zoneID) // Left
						{ 
							change.X = -1;
							change.Y = 0;
							wasVertical = false;
						}
						else if(currentMap.processedAIMap[coord.Y][coord.X + 1] == zoneID) //Right
						{ 
							change.X = 1;
							change.Y = 0;
							wasVertical = false;
						}
					}
				}
			}
		}

		//Prevents oldCoord from being changed if the ghost did not move at all
		if ((change.X != 0 || change.Y != 0) && oldCoordsNotSet)
		{
			oldCoord = coord;
			oldCoordsNotSet = false;
		}
		coord.X += change.X;
		coord.Y += change.Y;
	}
}

bool Ghost::isHitByBullet(Bullet shot, Map &currentMap)
{
	for (int position = 0; position < shot.speed; ++position)
	{
		if(coord.X == shot.coord.X - (shot.change.X * position) && coord.Y == shot.coord.Y - (shot.change.Y * position))
		{
			return true;
		}
	}

	return false;
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
			srand(static_cast<unsigned int>(time(NULL)));
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

Pacman::Pacman(Map &currentMap, int playerLives, COLOR playerColour)
{
	health = 1;
	speed = 1;
	lives = playerLives;
	color = playerColour;
	coord.X = currentMap.startPos.X;
	coord.Y = currentMap.startPos.Y;
	oldCoord = coord;
	direct = E_RIGHT_DIRECTION;
	currentPowerColourBlink = 0;

	for (size_t i = 0; i < E_MAX_POWER_UPS; ++i)
	{
		powerUpsActive[i] = false;
	}
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
	COLOR currentColour = color;

	if (currentPowerColourBlink == E_MAX_POWER_UPS)
	{
		currentPowerColourBlink = 0;
	}

	if (powerUpsActive[currentPowerColourBlink])
	{
		switch(currentPowerColourBlink)
		{
			case E_LIFE_POWER_UP:
				currentColour = E_RED_COLOR;
				break;
			case E_SPEED_POWER_UP:
				currentColour = E_CYAN_COLOR;
				break;
			case E_DAMAGE_POWER_UP:
				currentColour = E_MAGENTA_COLOR;
				break;
			case E_MULTIPLIER_POWER_UP:
				currentColour = E_LIGHT_GREEN_COLOR;
				break;
		}
	}

	++currentPowerColourBlink;

	colour(getColourWORD(currentColour));

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

	if (powerUpsActive[E_LIFE_POWER_UP])
	{
		powerUpsActive[E_LIFE_POWER_UP] = false;
	}
}

void Pacman::undraw(Map &currentMap)
{
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord, currentMap.colors);
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
	for(int position = 0; position < enemy.speed; ++position)
	{
		if(coord.X == enemy.coord.X - (enemy.change.X * position) && coord.Y == enemy.coord.Y - (enemy.change.Y * position))
		{
			Beep(200, 100);
			return true;
		}
	}

	return false;
}