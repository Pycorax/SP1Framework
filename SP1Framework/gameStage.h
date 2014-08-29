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
	E_GAME_GUIDE,
	E_EXIT,
	E_MAX_GAME_STATES
};

extern struct Loadables;

void mainMenu(GAMESTATE &game);
void gameLoop(string maps[], const size_t NUM_OF_MAPS, GAMESTATE &game, Loadables &loads);
bool pauseMenu(E_LEVEL_STATE &levelState, Loadables loads);
void loadCustomGame(GAMESTATE &game);
bool quit(GAMESTATE &game);

//Save & Load
void saveMenu(Loadables loads);
void loadMenu(GAMESTATE &game, Loadables &loadInfo);

//Between Level Screens
void loadingScreen(string mapName);
void startScreen(string mapName);

//Delete Menus
void deleteMenu(GAMESTATE &game);
bool deleteMenu();

//Victory/Lose Screens
void endScreen();
void winScreen();
void victoryScreen();
void loseScreen();
void gameOver(GAMESTATE &game);

//Others
void highScoreBoard(int scorePoints);
void gameGuide(GAMESTATE &game);

#endif