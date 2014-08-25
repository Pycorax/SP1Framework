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
	GAME_OVER,
	MAX_STATES
};

void mainMenu(gameState &game);
void gameLoop(string maps[], gameState &game);
void gameOver(gameState &game);
bool quit(gameState &game);

#endif