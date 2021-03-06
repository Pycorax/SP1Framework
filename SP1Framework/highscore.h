#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <string>
#include "gameStage.h"

using std::string;

struct playerScore
{
	string names;
	int score;
	string mapName;
};

void sortScore(playerScore * playerScore,int scorePoint,string playerName, string mapName);
void highScoreBoard(int scorePoint, string mapName);
void highScoreBoard();
void displayScores(playerScore * playerScore);
void storeScore(int scorePoint);
void read(string fileName, playerScore * playerScore);
void write(string fileName, playerScore * playerScore);
void highScoreTitle();

#endif