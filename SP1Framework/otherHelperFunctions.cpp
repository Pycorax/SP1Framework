#include "otherHelperFunctions.h"
#include <sstream>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "Framework/console.h"

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
	Sleep(300);
	string text = "Press any key to continue...";
	gotoXY(consoleSize.X/2 - text.length()/2, y_coord);
	cout << text;

	flushInputBuffer();
	gotoXY(consoleSize.X/2, y_coord + 1);
	_getch();
	flushInputBuffer();
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