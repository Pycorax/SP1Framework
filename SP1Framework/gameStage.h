#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <string>

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
void gameLoop(string maps[]);
bool quit(gameState &game);

#endif