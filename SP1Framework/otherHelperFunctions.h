#ifndef OTHER_HELPER_FUNCTIONS_H
#define OTHER_HELPER_FUNCTIONS_H

#include <Windows.h>
#include <string>

using std::string;

void newSetConsoleSize(COORD size);
void newSetConsoleSize(int x, int y);
void flushInputBuffer();
void pressToContinue(int y_coord);
void clearInput();
bool fileExists(string saveName);
bool isNumber(char test);
short charToNumber(char number); //Returns -1 if is not a number

#endif