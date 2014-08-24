#include "userInterface.h"
#include <iostream>

using std::cout;

void printInterface(int score)
{
	cout << "Score: " << score;
}

void printminScore(int minScore)
{
	minScore = 20000;
	cout << "Minimum Score: " << minScore;
}

void printBlank(int blanks)
{
	cout << "                                                                                                                        ";
}