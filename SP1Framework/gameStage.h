#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <string>
#include "maps.h"

using std::string;

enum gameState
{
	MAIN_MENU,
	LOAD_MENU,
	GAME,
	QUIT_MENU,
	EXIT,
	MAX_STATES
};

void mainMenu(gameState &game);
void gameLoop(string maps[], gameState &game, unsigned int level = 0);
//Pause stuff
void saveMenu(E_LEVEL_STATE levelState);

void loadMenu(gameState &game, unsigned int &level);
bool quit(gameState &game);

#endif