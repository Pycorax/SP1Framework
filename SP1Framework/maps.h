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
#include "characters.h"

;using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

extern struct Ghost;

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

	ZoneBounds(vector<vector<char>> processedAIMap, unsigned short zone);
};

struct Map
{
	unsigned short ghosts;
	int minScore;
	unsigned short zones;
	COORD startPos;
	vector<ZoneBounds> zoneCoords;
	vector<vector<char>> processedMap;
	vector<vector<char>> processedAIMap;
	vector<Ghost> ghostStorage;

	Map(const char mapName[], const char aiMapName[]);
	//TODO: Create destructor for Map when level system is added
	//~Map();

	bool processMap(const char mapName[]);
	bool processAIMap(const char mapName[]);
	void renderMap();
};

void printTile(char tile, COORD tileLocation);

void gotoXYTile(int x, int y);
void gotoXYTile(COORD location);
void gotoXYTileDown(COORD location, unsigned short downBy);
void gotoXYTileUp(COORD location, unsigned short upBy);
void gotoXYTileLeft(unsigned short leftBy , COORD location);
void gotoXYTileRight(unsigned short rightBy , COORD location);

#endif