#include "otherHelperFunctions.h"
#include <sstream>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "Framework/console.h"
#include "game.h"

using std::ostringstream;
using std::cout;
using std::ifstream;

extern COORD consoleSize;

void newSetConsoleSize(COORD size)
{
	newSetConsoleSize(size.X, size.Y);
}

void newSetConsoleSize(int x, int y)
{
	const int MIN_X = 66;
	const int MIN_Y = 37;

	if (x < MIN_X)
	{
		x = MIN_X;
	}

	if (y < MIN_Y)
	{
		y = MIN_Y;
	}

	consoleSize.X = x;
	consoleSize.Y = y;

	ostringstream oss;
	oss << "mode " << x << "," << y;

	system(oss.str().c_str());
}

void flushInputBuffer()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hIn);
}

void pressToContinue(int y_coord)
{
	extern bool keyPressed[E_MAX_KEYS];

	Sleep(300);
	string text = "Press Up to continue...";
	gotoXY(consoleSize.X/2 - text.length()/2, y_coord);
	cout << text;

	gotoXY(consoleSize.X/2, y_coord + 1);
	
	while(true)
	{
		getInput();

		if(keyPressed[E_UP_KEY])
		{
			break;
		}
	}
}

void pressToContinue()
{
	extern bool keyPressed[E_MAX_KEYS];

	Sleep(300);
	cout << "Press Up to continue...";

	while(true)
	{
		getInput();

		if(keyPressed[E_UP_KEY])
		{
			break;
		}
	}
}

bool fileExists(string saveName)
{
	ifstream file;

	file.open(saveName.c_str());

	if(file.is_open())
	{
		string firstLine;
		getline(file, firstLine);
		file.close();

		if(firstLine == "")
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool isNumber(char test)
{
	if (test >= '0' && test <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

short charToNumber(char number)
{
	if (isNumber(number))
	{
		return number - 48;
	}
	else
	{
		return -1;
	}
}