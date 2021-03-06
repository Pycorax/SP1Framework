#ifndef _GAME_H
#define _GAME_H

#include "maps.h"
#include "characters.h"
#include "gameStage.h"
#include "saves.h"

extern "C"
{
	struct Ghost;
	struct Pacman;
	struct Map;
	struct Bullet;
	struct Loadables;
};

enum KEYS
{
    E_UP_KEY,
    E_DOWN_KEY,
    E_LEFT_KEY,
    E_RIGHT_KEY,
    E_ESCAPE_KEY,
	E_SPACE_KEY,
	E_ENTER_KEY,
    E_MAX_KEYS
};

void init();																									// initialize your variables, allocate memory, etc
void getInput();																								// get input from player
void clearInput();
void update(double dt, Map &currentMap, Pacman &player);														// update the game and the state of the game
void render(Map &currentMap, Pacman &player, Loadables loads, OptionSet options, bool isCustom = false);		// renders the current state of the game to the console
void shutdown();																								// do clean up, free memory
void levelLoop(string mapName, GAMESTATE &game, unsigned int level, Loadables &loads, OptionSet options);
void customLevelLoop(string mapName, Loadables loads, OptionSet options);

#endif // _GAME_H