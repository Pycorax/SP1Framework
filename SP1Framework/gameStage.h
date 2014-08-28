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
	E_LOSS_SCREEN,
	E_HIGH_SCORES,
	E_EXIT,
	E_MAX_GAME_STATES
};

extern struct Loadables;

void mainMenu(GAMESTATE &game);
void gameLoop(string maps[], const size_t NUM_OF_MAPS, GAMESTATE &game, Loadables &loads);
void saveMenu(Loadables loads);
void loadMenu(GAMESTATE &game, Loadables &loadInfo);
bool pauseMenu(E_LEVEL_STATE &levelState, Loadables loads);
void loadingScreen(string mapName);
void gameOver(GAMESTATE &game);
void startScreen(string mapName);
//void endScreen();
bool quit(GAMESTATE &game);
void deleteMenu(GAMESTATE &game);
bool deleteMenu();
void endScreen();
void winScreen();
void highScoreBoard(int scorePoints);
void victoryScreen();
void loseScreen();

#endif