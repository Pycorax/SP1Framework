#ifndef MAPS_H
#define MAPS_H

#include <vector>
#include <Windows.h>
#include "characters.h"
#include "bullet.h"
#include <string>

using std::vector;
using std::string;

extern struct Ghost;

enum DIRECTION
{
	E_LEFT_DIRECTION,
	E_RIGHT_DIRECTION,
	E_UP_DIRECTION,
	E_DOWN_DIRECTION,
	E_MAX_DIRECTION
};

struct ZoneBounds
{
	unsigned short minX;
	unsigned short minY;
	unsigned short maxX;
	unsigned short maxY;

	ZoneBounds(vector<vector<char>> processedAIMap, unsigned short zone);
};

struct GhostData
{
	short health;
	short speed;
	unsigned short respawnDelay;
	unsigned short numericZoneID;
};

struct Map
{
	int scorePoints;
	unsigned short ghosts;
	unsigned short zones;
	int minScore;
	int pellets;
	COORD startPos;
	vector<ZoneBounds> zoneCoords;
	vector<vector<char>> processedMap;
	vector<vector<char>> processedAIMap;
	vector<Ghost> ghostStorage;
	vector<GhostData> *ghostDataStorage; //To get values to initialize Ghosts
	Bullet *shot;
	bool valid;

	Map(string mapName);
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
bool isOppositeDirection(DIRECTION direct, DIRECTION otherDirect);

#endif