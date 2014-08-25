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
	PAUSE_MENU,
	EXIT,
	MAX_STATES
};

void mainMenu(gameState &game);
void gameLoop(string maps[], gameState &game);
void gameLoop(string maps[]);
void pauseMenu();
void loadingScreen(string mapName);
void startScreen(string mapName);
void endScreen();
bool quit(gameState &game);

#endif