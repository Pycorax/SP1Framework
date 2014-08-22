#include "Framework\timer.h"

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 5; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame