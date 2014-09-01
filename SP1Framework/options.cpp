#include "options.h"
#include "Framework/console.h"
#include <fstream>
#include "otherHelperFunctions.h"

using std::ofstream;
using std::ifstream;
using std::endl;

OptionSet::OptionSet()
{
	playerColour = E_WHITE_COLOR;
	wallColour = E_WHITE_COLOR;
	pelletColour = E_WHITE_COLOR;
}

OptionSet::OptionSet(COLOR player, COLOR wall, COLOR pellet)
{
	playerColour = player;
	wallColour = wall;
	pelletColour = pellet;
}

WORD getColourWORD(COLOR color) //Sets the colour according to the enum COLOR given
{
	WORD finalColour;

	//Base colours
	if (color >= E_RED_COLOR && color <= E_MAGENTA_COLOR) //Red Base
	{
		finalColour = FOREGROUND_RED;

		if (color == E_YELLOW_COLOR)
		{
			finalColour |= FOREGROUND_GREEN;
			finalColour |= FOREGROUND_INTENSITY;
		}

		if (color == E_PURPLE_COLOR || color == E_MAGENTA_COLOR)
		{
			finalColour |= FOREGROUND_BLUE;
		}

		//Intensity
		if (color >= E_BRIGHT_RED_COLOR && color <= E_MAGENTA_COLOR)
		{
			finalColour |= FOREGROUND_INTENSITY;
		}
	}
	else if (color >= E_BLUE_COLOR && color <= E_LIGHT_BLUE_COLOR) //Blue Base
	{
		finalColour = FOREGROUND_BLUE;

		if (color >= E_TEAL_COLOR && color <= E_CYAN_COLOR)
		{
			finalColour |= FOREGROUND_GREEN;
		}

		//Intensity
		if (color == E_CYAN_COLOR || color == E_LIGHT_BLUE_COLOR)
		{
			finalColour |= FOREGROUND_INTENSITY;
		}

	}
	else if (color >= E_GREEN_COLOR && color <= E_OLIVE_COLOR) // Green Base
	{
		finalColour = FOREGROUND_GREEN;

		if (color >= E_YELLOW_COLOR && color <= E_OLIVE_COLOR)
		{
			finalColour |= FOREGROUND_RED;
		}

		if (color == E_LIGHT_GREEN_COLOR || color == E_YELLOW_COLOR)
		{
			finalColour |= FOREGROUND_INTENSITY;
		}
	}
	else if (color >= E_BLACK_COLOR && color <= E_DARK_GREY_COLOR)
	{
		finalColour = 0;

		if (color == E_DARK_GREY_COLOR)
		{
			finalColour |= FOREGROUND_INTENSITY;
		}
	}
	else
	{
		finalColour = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;

		if (color == E_WHITE_COLOR)
		{
			finalColour |= FOREGROUND_INTENSITY;
		}
	}

	return finalColour;
}

bool saveOptions(OptionSet &options, OptionSet newOptions)
{
	ofstream saveFile;
	string directory = "Saves/";
	string fullFileName = directory + "options.cfg";

	options = newOptions;

	saveFile.open(fullFileName.c_str());
	if(saveFile.is_open())
	{
		saveFile << options.playerColour << endl;
		saveFile << options.wallColour << endl;
		saveFile << options.pelletColour << endl;
		saveFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool loadOptions(OptionSet &options)
{
	ifstream optionFile;
	string directory = "Saves/";
	string fullFileName = directory + "options.cfg";
	string input;

	if(fileExists(fullFileName))
	{
		optionFile.open(fullFileName.c_str());
		getline(optionFile, input);
		options.playerColour = static_cast<COLOR>(atoi(input.c_str()));
		getline(optionFile, input);
		options.wallColour = static_cast<COLOR>(atoi(input.c_str()));
		getline(optionFile, input);
		options.pelletColour = static_cast<COLOR>(atoi(input.c_str()));

		optionFile.close();

		return true;
	}
	else
	{
		return false;
	}
}