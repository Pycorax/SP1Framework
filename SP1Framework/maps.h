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

bool processMap(const char mapName[], vector<vector<char>> &processedMap);
void renderMap(vector<vector<char>> processedMap);
void loadMap(const char mapName[], vector<vector<char>> &processedMap);
void printTile(char tile, COORD tileLocation);
void printPlayer(COORD charLocation, direction charDirection);

#endif