#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <Windows.h>

using std::string;

enum COLOR
{
	//Red Base
	E_RED_COLOR,
	E_PURPLE_COLOR,
	//Need intensity
	E_BRIGHT_RED_COLOR,
	E_MAGENTA_COLOR,

	//Blue Base
	E_BLUE_COLOR,
	E_TEAL_COLOR,
	//Need Intensity
	E_CYAN_COLOR,
	E_LIGHT_BLUE_COLOR,

	//Green Base
	E_GREEN_COLOR,
	//Need Intensity
	E_LIGHT_GREEN_COLOR,
	E_YELLOW_COLOR,
	E_OLIVE_COLOR,

	//All Base
	E_GREY_COLOR,
	E_WHITE_COLOR,

	//0 Base
	E_BLACK_COLOR,
	E_DARK_GREY_COLOR,

	E_MAX_COLORS
};

struct OptionSet
{
	COLOR playerColour;
	COLOR wallColour;
	COLOR pelletColour;

	OptionSet();
	OptionSet(COLOR player, COLOR wall, COLOR pellet);
};

WORD getColourWORD(COLOR color = E_WHITE_COLOR);
bool saveOptions(OptionSet &options, OptionSet newOptions);
bool loadOptions(OptionSet &options);

#endif