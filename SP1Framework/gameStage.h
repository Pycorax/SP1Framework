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
	GAME_OVER,
	QUIT_MENU,
	EXIT,
	MAX_STATES
};

void mainMenu(gameState &game);
void gameLoop(string maps[], const size_t NUM_OF_MAPS, gameState &game);
bool pauseMenu(E_LEVEL_STATE &levelState);
void loadingScreen(string mapName);
void gameOver(gameState &game);
void startScreen(string mapName);
void endScreen();
void winScreen();
void highScoreBoard(int scorePoints);
bool quit(gameState &game);

#endif