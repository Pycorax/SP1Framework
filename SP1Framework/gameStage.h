#ifndef GAME_STAGE_H
#define GAME_STAGE_H

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
bool quit(gameState &game);

#endif