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

void printScore(int score, int minScore, OptionSet options)
{
	colour(getBGColourWORD(options.hudBGColour) | getColourWORD(options.hudTextColour));
	gotoXY(0, 2);
	cout << "Level Score: ";
	const short MAX_SCORE_LENGTH = 5;
	cout << setw(MAX_SCORE_LENGTH) << setfill(' ');
	cout << score;
	cout << " / " << minScore;
}

void printLevelName(string mapName, OptionSet options)
{
	colour(getBGColourWORD(options.hudBGColour) | getColourWORD(options.hudTextColour));
	gotoXY(0,0);
	cout << "Map Name: " << mapName;
}

void printHUDBackground(BG_COLOR bgColor)
{
	colour(getBGColourWORD(bgColor));
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
	
	gotoXY(0,consoleSize.Y);
	for(size_t i = 0; i < consoleSize.X; ++i)
	{
		cout << "*";
	}
}

void printPellets(int pellets, OptionSet options)
{
	const short MAX_PELLET_LENGTH = 3;
	string output = " Pellets Left";
	colour(getBGColourWORD(options.hudBGColour) | getColourWORD(options.hudTextColour));
	gotoXY(consoleSize.X - output.length() - MAX_PELLET_LENGTH, 2);
	cout << setw(MAX_PELLET_LENGTH) << setfill(' ');
	cout << pellets;
	cout << output;
}

void printLives(int lives, OptionSet options)
{
	const short MAX_LIFE_LENGTH = 6;
	string output = " Lives";
	colour(getBGColourWORD(options.hudBGColour) | getColourWORD(options.hudTextColour));
	gotoXY(consoleSize.X - output.length() - MAX_LIFE_LENGTH, 0);
	cout << setw(MAX_LIFE_LENGTH) << setfill(' ');
	cout << lives;
	cout << output;
}

void printLevel(int level, OptionSet options)
{
	ostringstream oss;
	oss << "Level " << level;

	colour(getBGColourWORD(options.hudBGColour) | getColourWORD(options.hudTextColour));
	gotoXY(consoleSize.X/2 - oss.str().length()/2, 1);
	cout << oss.str();
}

void printCumulativeScore(int score, int cumulativeScore, OptionSet options)
{
	colour(getBGColourWORD(options.hudBGColour) | getColourWORD(options.hudTextColour));
	gotoXY(0,1);
	cout << "Total Score: ";
	cout << cumulativeScore + score;
}

void printControls()
{
	colour(getColourWORD(E_WHITE_COLOR));

	if (consoleSize.X >  56)
	{
		printControlsSplit();
	}
	else
	{
		printControlsCenter();
	}
}

void printControlsSplit()
{
	const int PADDING = 8;

	gotoXY(PADDING, consoleSize.Y - PADDING);
	cout << "Arrow Keys - Navigation";

	string rightIns = "[ space ] - Select";
	gotoXY(consoleSize.X - PADDING - rightIns.length(), consoleSize.Y - PADDING);
	cout << rightIns;
}

void printControlsCenter()
{
	const int PADDING = 4;

	string leftIns =  "Arrow Keys - Navigation";
	gotoXY(consoleSize.X/2 - leftIns.length()/2, consoleSize.Y - PADDING);
	cout << leftIns;

	string rightIns = "[ space ] - Select";
	gotoXY(consoleSize.X/2 - rightIns.length()/2, consoleSize.Y - PADDING);
	cout << rightIns;
}

void printOptionsControls()
{
	const int PADDING = 8;

	string leftIns = "Up/Down Keys - Navigation";
	gotoXY(PADDING, consoleSize.Y - PADDING);
	cout << leftIns;

	string midIns = "Left/Right Keys - Cycle Through Options";
	gotoXY(consoleSize.X/2 - midIns.length()/2, consoleSize.Y - PADDING);
	cout << midIns;

	string rightIns = "[ space ] - Select";
	gotoXY(consoleSize.X - PADDING - rightIns.length(), consoleSize.Y - PADDING);
	cout << rightIns;
}