#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "maps.h"
#include "characters.h"

;using std::vector;
extern StopWatch g_timer;
extern bool g_quitGame;
extern struct Ghost;
extern struct Pacman;
extern struct Map;
extern struct Bullet;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,
    K_COUNT
};

void init();												// initialize your variables, allocate memory, etc
void getInput();											// get input from player
void update(double dt, Map &currentMap, Pacman &player, Bullet &shoot);	// update the game and the state of the game
void render(Map &currentMap, Pacman &player,Bullet &shoot);			// renders the current state of the game to the console
void shutdown();											// do clean up, free memory

#endif // _GAME_H