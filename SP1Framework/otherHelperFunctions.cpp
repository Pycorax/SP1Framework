#include "otherHelperFunctions.h"
#include <sstream>
#include <string>
#include <iostream>
#include <conio.h>
#include "Framework/console.h"

using std::ostringstream;
using std::string;
using std::cout;

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