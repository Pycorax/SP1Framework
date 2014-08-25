#include "userInterface.h"
#include <iostream>
#include "maps.h"
#include "Framework/console.h"

using std::cout;
using std::endl;

extern COORD consoleSize;

void printInterface(int score)
{
	colour(BACKGROUND_GREEN);
	cout << "Score: " << score;
}

void printMinScore(int minScore)
{
	colour(BACKGROUND_GREEN);
	cout << "Minimum Score: " << minScore;
}

void printHUDBackground()
{
	colour(BACKGROUND_GREEN);
	for(int j = 0; j < HUD_OFFSET; ++j)
	{
		gotoXY(0,0 + j);
		for(int i = 0; i < consoleSize.X; ++i)
		{
			cout << " ";
		}
	}
}

void printBorder()
{
	colour(FOREGROUND_GREEN | FOREGROUND_RED);
	gotoXY(0,2);
	for(size_t i = 0; i < consoleSize.X; ++i)
	{
		cout << "*";
	}

	for(size_t i = 0; i < consoleSize.Y; ++i)
	{
		gotoXY(0,i);
		cout << "*";
		gotoXY(consoleSize.X-1, i);
		cout << "*";
	}

	gotoXY(0,consoleSize.Y + 2);
	for(size_t i = 0; i < consoleSize.X; ++i)
	{
		cout << "*";
	}
}

void printPellets(int pellets)
{
	colour(BACKGROUND_GREEN);
	cout << "Remaining Pellets: " << pellets;
}