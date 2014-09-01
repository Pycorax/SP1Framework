#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <string>
#include "maps.h"
#include "saves.h"
#include "options.h"

using std::string;

enum GAMESTATE
{
	E_MAIN_MENU,
	E_GAME,
	E_LOAD_SAVES,
	E_LOAD_CUSTOM,
	E_GAME_GUIDE,
	E_DELETE_SAVES,
	E_HIGH_SCORES,
	E_OPTIONS_MENU,
	E_ABOUT_SCREEN,
	E_QUIT_MENU,
	E_GAME_OVER,
	E_LOSS_SCREEN,
	E_EXIT,
	E_MAX_GAME_STATES
};

extern struct Loadables;
extern struct OptionSet;

void mainMenu(GAMESTATE &game);
void gameLoop(string maps[], const size_t NUM_OF_MAPS, GAMESTATE &game, Loadables &loads, OptionSet options);
bool pauseMenu(E_LEVEL_STATE &levelState, Loadables loads, bool isCustom = false);
void saveMenu(GAMESTATE &game);
void optionsMenu(GAMESTATE &game, OptionSet &options);
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

//Custom Maps
void loadCustomLevelMenu(GAMESTATE &game, OptionSet options);
void customGame(string mapName, OptionSet options);

//Others
void highScoreBoard(int scorePoints);
void gameGuide(GAMESTATE &game);
void aboutScreen();

#endif