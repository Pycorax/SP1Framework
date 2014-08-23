#include "maps.h"
#include <fstream>
#include <iostream>
#include "Framework\console.h"
#include "userInterface.h"

using std::ifstream;
using std::cout;

ZoneBounds::ZoneBounds(vector<vector<char>> processedAIMap, unsigned short zone)
{
	char zoneID = zone + 48;
	bool first = true;

	for (size_t y = 0; y < processedAIMap.size(); ++y)
	{
		for (size_t x = 0; x < processedAIMap[y].size(); ++x)
		{
			if(processedAIMap[y][x] == zoneID && first)
			{
				minX = x;
				minY = y;
				first = false;
			}

			if(processedAIMap[y][x] == zoneID)
			{
				maxX = x;
				maxY = y;
			}
		}
	}
}

Map::Map(string mapName)
{
	ghostDataStorage = new vector<GhostData>;

	//Get names of the map files
	string actualMapName = mapName + ".map";
	string aiMapName = mapName + ".aimap";

	//Process the map files
	processMap(actualMapName.c_str());
	processAIMap(aiMapName.c_str());

	//Get the Zone Bounds
	ZoneBounds *zoneptr = NULL;

	for (unsigned short i = 0; i < zones; ++i)
	{
		zoneptr = new ZoneBounds(processedAIMap, i);
		zoneCoords.push_back(*zoneptr);
	}

	//Create the Ghosts
	Ghost *newGhost = NULL;

	for(size_t i = 0; i < ghosts; ++i)
	{
		newGhost = new Ghost((*ghostDataStorage)[i].health, (*ghostDataStorage)[i].speed, (*ghostDataStorage)[i].numericZoneID, (*ghostDataStorage)[i].respawnDelay, *this);

		ghostStorage.push_back(*newGhost);
	}

	//Delete Ghost Data
	delete ghostDataStorage;

	//Count pellets on map
	pellets = 0;
	for(size_t row = 0; row < processedMap.size(); ++row)
	{
		for(size_t column = 0; column < processedMap[row].size(); ++column)
		{
			if(processedMap[row][column] == '.')
			{
				++pellets;
			}
		}
	}

	//Initialize other values
	shot = NULL;
	scorePoints = 0;
}

bool Map::processMap(const char mapName[])
{
	string readLine;
	char readChar;
	bool skipLine = false;

	ifstream mapFile;
	mapFile.open(mapName);

	if(mapFile.is_open())
	{
		for (int coord_y = 0; !mapFile.eof() ; ++coord_y)
		{
			getline(mapFile, readLine);
			
			vector<char> *ptr = new vector<char>;

			for (size_t coord_x = 0; coord_x < readLine.length() ; ++coord_x)
			{
				skipLine = false;
				readChar = readLine[coord_x];
				if(readChar == 'G')
				{
					--coord_y;
					getline(mapFile, readLine);
					ghosts = atoi(readLine.c_str());
					skipLine = true;
					break;
				}
				else if(readChar == 'Z')
				{
					--coord_y;
					getline(mapFile, readLine);
					zones = atoi(readLine.c_str());
					skipLine = true;
					break;
				}
				else if(readChar == 'D')
				{
					GhostData *ptr = new GhostData;

					--coord_y;
					getline(mapFile, readLine);
					(*ptr).health = atoi(readLine.c_str());

					getline(mapFile, readLine);
					(*ptr).speed = atoi(readLine.c_str());

					getline(mapFile, readLine);
					(*ptr).respawnDelay = atoi(readLine.c_str());

					getline(mapFile, readLine);
					(*ptr).numericZoneID = atoi(readLine.c_str());

					ghostDataStorage->push_back(*ptr);

					skipLine = true;
					break;
				}
				else if(readChar == 'S')
				{
					--coord_y;
					getline(mapFile, readLine);
					minScore = atoi(readLine.c_str());
					skipLine = true;
					break;
				}
				else
				{
					if(readChar == 'P')
					{
						startPos.Y = coord_y;
						startPos.X = coord_x;
					}

					ptr->push_back(readChar);
				}
			}

			if(!skipLine)
			{
				processedMap.push_back(*ptr);
			}
		}

		mapFile.close();

		return true;
	}
	else
	{
		return false;
	}
}

bool Map::processAIMap(const char mapName[])
{
	string readLine;
	char readChar;

	ifstream mapFile;
	mapFile.open(mapName);

	if(mapFile.is_open())
	{
		for (int coord_y = 0; !mapFile.eof() ; ++coord_y)
		{
			getline(mapFile, readLine);
			
			vector<char> *ptr = new vector<char>;

			for (size_t coord_x = 0; coord_x < readLine.length() ; ++coord_x)
			{
				readChar = readLine[coord_x];
				ptr->push_back(readChar);
			}

			processedAIMap.push_back(*ptr);
		}

		mapFile.close();

		return true;
	}
	else
	{
		return false;
	}
}

void Map::renderMap()
{
	const char border = 176;
	const char space = ' ';
	const char obstacle = 176;
	const char pellet = 'o';

	//Controls Rows
	for (size_t coord_y = 0; coord_y < processedMap.size(); ++coord_y)
	{
		//Controls Columns
		for (size_t coord_x = 0; coord_x < processedMap[coord_y].size(); ++coord_x)
		{	
			COORD tileLocation;
			tileLocation.X = coord_x;
			tileLocation.Y = coord_y;
			printTile(processedMap[coord_y][coord_x], tileLocation);
		}
	}
}

void printTile(char tile, COORD tileLocation)
{
	const char border = 176;
	const char space = ' ';
	const char obstacle = 176;
	const char pellet = 'o';

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	switch(tile)
	{
		case'#':
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXYTileDown(tileLocation, height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					cout << border;
				}
			}
			break;
		case'O':
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXYTileDown(tileLocation, height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					cout << obstacle;
				}
			}
			break;
		case '.':
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXYTileDown(tileLocation, height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					if (height == 1 && width == 1)
					{
						cout << pellet;
					}
					else
					{
						cout << space;
					}
				}
			}
			break;
		default:
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXYTileDown(tileLocation, height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					cout << space;
				}
			}
			break;
	}
}

void gotoXYTile(int x, int y)
{
	COORD location;
	location.X = x;
	location.Y = y;

	gotoXYTile(location);
}

void gotoXYTile(COORD location)
{
	COORD tileLocation;

	tileLocation.X = location.X * TILE_WIDTH;
	tileLocation.Y = location.Y * TILE_HEIGHT + HUD_OFFSET;

	gotoXY(tileLocation);
}

void gotoXYTileDown(COORD location, unsigned short downBy)
{
	COORD tileLocation;

	if(downBy <= TILE_HEIGHT)
	{
		tileLocation.X = location.X * TILE_WIDTH;
		tileLocation.Y = location.Y * TILE_HEIGHT + HUD_OFFSET + downBy;

		gotoXY(tileLocation);
	}
}

bool isOppositeDirection(DIRECTION direct, DIRECTION otherDirect)
{
	if(direct == otherDirect)
	{
		return false;
	}

	switch(direct)
	{
		case E_UP_DIRECTION:
			if(otherDirect == E_DOWN_DIRECTION)
			{
				return true;
			}
			break;
		case E_DOWN_DIRECTION:
			if(otherDirect == E_UP_DIRECTION)
			{
				return true;
			}
			break;
		case E_LEFT_DIRECTION:
			if(otherDirect == E_RIGHT_DIRECTION)
			{
				return true;
			}
			break;
		case E_RIGHT_DIRECTION:
			if(otherDirect == E_LEFT_DIRECTION)
			{
				return true;
			}
			break;
	}

	return false;
}