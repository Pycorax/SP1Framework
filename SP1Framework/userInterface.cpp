#include "userInterface.h"
#include <iostream>
#include "maps.h"
#include "Framework/console.h"
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

extern COORD consoleSize;

void printScore(int score)
{
	ostringstream output;
	output << "Score: " << score;
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(consoleSize.X - output.str().length(), 1);
	cout << output.str();
}

void printMinScore(int minScore)
{
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(0,2);
	cout << "Minimum Score to Hit: " << minScore;
}

void printLevelName(string mapName)
{
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(0,1);
	cout << "Map: " << mapName;
}

void printHUDBackground()
{
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
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
	ostringstream output;
	output << "Pellets Remaining: " << pellets;
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(consoleSize.X - output.str().length(), 2);
	cout << output.str();
}

void printLives(int lives)
{
	ostringstream output;
	output << "Lives: " << lives;
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(consoleSize.X - output.str().length(), 0);
	cout << output.str();
}