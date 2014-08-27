#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <string>
#include "maps.h"
#include "saves.h"

using std::string;

enum GAMESTATE
{
	E_MAIN_MENU,
	E_LOAD_MENU,
	E_DELETE_SAVES,
	E_GAME,
	E_GAME_OVER,
	E_QUIT_MENU,
	E_EXIT,
	E_MAX_GAME_STATES
};

void mainMenu(GAMESTATE &game);
void gameLoop(string maps[], const size_t NUM_OF_MAPS, GAMESTATE &game, Loadables loads);
void saveMenu(unsigned int level, int playerLives);
void loadMenu(GAMESTATE &game, Loadables &loadInfo);
bool pauseMenu(E_LEVEL_STATE &levelState, unsigned int level, int playerLives);
void loadingScreen(string mapName);
void gameOver(GAMESTATE &game);
void startScreen(string mapName);
//void endScreen();
bool quit(GAMESTATE &game);
void deleteMenu(GAMESTATE &game);
bool deleteMenu();

#endif