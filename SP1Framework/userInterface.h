#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

using std::string;

const size_t HUD_OFFSET = 3;
const size_t TILE_WIDTH = 3;
const size_t TILE_HEIGHT = 3;

void printScore(int score, int minScore);
void printLevelName(string mapName);
void printHUDBackground();
void printBorder();
void printPellets(int pellets);
void printLives(int lives);
void printLevel(int level);
void printCumulativeScore(int score, int cumulativeScore);
#endif