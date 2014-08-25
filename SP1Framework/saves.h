#ifndef SAVES_H
#define SAVES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

bool saveGame(unsigned int level, string saveName);
int loadGame(unsigned int &level, string saveName);
int findSaveFiles(vector<string> &fileNames); //Stores list of save files in fileNames

#endif