#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

const size_t HUD_OFFSET = 3;
const size_t TILE_WIDTH = 3;
const size_t TILE_HEIGHT = 3;

void printInterface(int score);
void printMinScore(int minScore);
void printHUDBackground();
void printBorder();
void printPellets(int pellets);
#endif