#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "maps.h"
#include "characters.h"

extern struct Ghost;
extern struct Pacman;
extern struct Map;
extern struct Bullet;

enum KEYS
{
    E_UP_KEY,
    E_DOWN_KEY,
    E_LEFT_KEY,
    E_RIGHT_KEY,
    E_ESCAPE_KEY,
	E_SPACE_KEY,
    E_MAX_KEYS
};

void init();												// initialize your variables, allocate memory, etc
void getInput();											// get input from player
void update(double dt, Map &currentMap, Pacman &player);	// update the game and the state of the game
void render(Map &currentMap, Pacman &player);			// renders the current state of the game to the console
void shutdown();											// do clean up, free memory
void levelLoop(string mapName);

#endif // _GAME_H