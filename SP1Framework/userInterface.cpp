#include "userInterface.h"
#include <iostream>

using std::cout;

void printInterface(int score)
{
	cout << "Score: " << score;
}

void printminScore(int minScore)
{
	cout << "Minimum Score: " << minScore;
}

void printBlank(int width)
{
	for(size_t i = 0; i < width; ++i)
	{
		cout << " ";
	}
}