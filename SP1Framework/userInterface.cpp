#include "userInterface.h"
#include <iostream>
#include <iomanip>
#include "maps.h"
#include "Framework/console.h"
#include <sstream>

using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::ostringstream;

extern COORD consoleSize;

void printScore(int score, int minScore)
{
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(0, 2);
	cout << "Score: ";
	const short MAX_SCORE_LENGTH = 5;
	cout << setw(MAX_SCORE_LENGTH) << setfill(' ');
	cout << score;
	cout << " / " << minScore;
}

void printLevelName(string mapName)
{
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(0,0);
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
	const short MAX_PELLET_LENGTH = 3;
	string output = " Pellets Left";
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(consoleSize.X - output.length() - MAX_PELLET_LENGTH, 2);
	cout << setw(MAX_PELLET_LENGTH) << setfill(' ');
	cout << pellets;
	cout << output;
}

void printLives(int lives)
{
	const short MAX_LIFE_LENGTH = 6;
	string output = " Lives";
	colour(BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoXY(consoleSize.X - output.length() - MAX_LIFE_LENGTH, 0);
	cout << setw(MAX_LIFE_LENGTH) << setfill(' ');
	cout << lives;
	cout << output;
}

void printLevel(int level)
{
	ostringstream oss;
	oss << "Level " << level;

	gotoXY(consoleSize.X/2 - oss.str().length()/2, 1);
	cout << oss.str();
}