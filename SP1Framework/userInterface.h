#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>
#include "options.h"

using std::string;

const size_t HUD_OFFSET = 3;
const size_t TILE_WIDTH = 3;
const size_t TILE_HEIGHT = 3;

//Menu UI
void printBorder();
void printControls();
void printControlsSplit();
void printControlsCenter();
void printOptionsControls();

//In-Game UI
void printScore(int score, int minScore, OptionSet options);
void printLevelName(string mapName, OptionSet options);
void printHUDBackground(BG_COLOR bgColor);
void printPellets(int pellets, OptionSet options);
void printLives(int lives, OptionSet options);
void printLevel(int level, OptionSet options);
void printCumulativeScore(int score, int cumulativeScore, OptionSet options);

#endif