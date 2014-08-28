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
	MAX_STATES,
	GAME_GUIDE
};

void mainMenu(gameState &game);
void gameLoop(string maps[], gameState &game);
bool quit(gameState &game);
void victoryScreen();
void loseScreen();
void gameGuide(gameState &game);

#endif