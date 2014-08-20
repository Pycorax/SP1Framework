#ifndef MAPS_H
#define MAPS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Framework\console.h"
#include "userInterface.h"
#include "game.h"

using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

enum direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX_DIRECTIONS
};

struct ZoneBounds
{
	unsigned short minX;
	unsigned short minY;
	unsigned short maxX;
	unsigned short maxY;

	ZoneBounds(vector<vector<char>> processedAIMap, unsigned short zone)
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
};

struct Map
{
	unsigned short ghosts;
	int minScore;
	unsigned short zones;
	vector<ZoneBounds> zoneCoords;
	vector<vector<char>> processedMap;
	vector<vector<char>> processedAIMap;

	Map(const char mapName[], const char aiMapName[])
	{
		processMap(mapName);
		processAIMap(aiMapName);

		ZoneBounds *zoneptr = NULL;

		for (unsigned short i = 0; i < zones; ++i)
		{
			zoneptr = new ZoneBounds(processedAIMap, i);
			zoneCoords.push_back(*zoneptr);
		}
	}

	bool processMap(const char mapName[]);
	bool processAIMap(const char mapName[]);
	void renderMap();
};

void renderMap(vector<vector<char>> processedMap);
void loadMap(const char mapName[], vector<vector<char>> &processedMap);
void printTile(char tile, COORD tileLocation);
void printPlayer(COORD charLocation, direction charDirection);
void printGhost(COORD ghostLocation, direction ghostDirection);

#endif