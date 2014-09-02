#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <string>
#include <vector>
#include "gameStage.h"

using std::string;
using std::vector;

struct Scores
{
	string names;
	int score;
	string mapName;
};

void highScoreTitle();
void highScoreBoard(int scorePoint, string mapName);
void highScoreBoard();

void loadScore(vector<Scores> &scoreStore);
void saveScore(vector<Scores> &scoreStore);
void addScore(Scores newScore);

#endif