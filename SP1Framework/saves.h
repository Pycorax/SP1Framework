#ifndef SAVES_H
#define SAVES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Loadables
{
	unsigned int level;
	int playerLives;

	Loadables(unsigned int level, int playerLives);
};

bool saveGame(unsigned int level, int playerLives, string saveName);
int loadGame(Loadables &loadInfo, string saveName);
bool fileExists(string saveName);
int findSaveFiles(vector<string> &fileNames); //Stores list of save files in fileNames
int findSaveFiles();
bool deleteGame(string saveName);

#endif