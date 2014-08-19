#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <iostream>
#include <vector>
#include "maps.h"

using std::cout;
using std::cin;
using std::endl;

enum gameState
{
	MAIN_MENU,
	LOAD_MENU,
	GAME,
	QUIT_MENU,
	EXIT,
	MAX_STATES
};

void mainMenu();
bool quit(gameState &game);

#endif