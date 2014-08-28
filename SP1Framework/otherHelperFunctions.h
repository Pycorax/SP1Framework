#ifndef OTHER_HELPER_FUNCTIONS_H
#define OTHER_HELPER_FUNCTIONS_H

#include <Windows.h>

void newSetConsoleSize(COORD size);
void newSetConsoleSize(int x, int y);
void flushInputBuffer();
void pressToContinue(int y_coord);

#endif