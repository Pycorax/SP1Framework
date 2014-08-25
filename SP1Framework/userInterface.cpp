#include "userInterface.h"
#include <iostream>
#include "maps.h"
#include "Framework/console.h"

using std::cout;

extern COORD consoleSize;

void printInterface(int score)
{
	cout << "Score: " << score;
}

void printminScore(int minScore)
{
	cout << "Minimum Score: " << minScore;
}

void printBlank(int blanks)
{
	cout << "                                                                                                                        ";
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
	cout << "Remaining Pellets: " << pellets;
}

void printLives(int lives)
{
	cout << "Remaining Lives: " << lives;
}