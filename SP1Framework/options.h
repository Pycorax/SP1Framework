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

enum BG_COLOR
{
	//Red Base
	E_RED_BG_COLOR,
	E_PURPLE_BG_COLOR,
	//Need intensity
	E_BRIGHT_RED_BG_COLOR,
	E_MAGENTA_BG_COLOR,

	//Blue Base
	E_BLUE_BG_COLOR,
	E_TEAL_BG_COLOR,
	//Need Intensity
	E_CYAN_BG_COLOR,
	E_LIGHT_BLUE_BG_COLOR,

	//Green Base
	E_GREEN_BG_COLOR,
	//Need Intensity
	E_LIGHT_GREEN_BG_COLOR,
	E_YELLOW_BG_COLOR,
	E_OLIVE_BG_COLOR,

	//All Base
	E_GREY_BG_COLOR,
	E_WHITE_BG_COLOR,

	//0 Base
	E_BLACK_BG_COLOR,
	E_DARK_GREY_BG_COLOR,

	E_MAX_BG_COLORS
};

struct OptionSet
{
	//Game
	COLOR playerColour;
	COLOR bulletColour;
	COLOR wallColour;
	COLOR pelletColour;

	//HUD
	COLOR hudTextColour;
	BG_COLOR hudBGColour;

	OptionSet();
	OptionSet(COLOR player, COLOR bullet, COLOR wall, COLOR pellet, COLOR hudText, BG_COLOR hudBG);
};

WORD getColourWORD(COLOR color = E_WHITE_COLOR);
WORD getBGColourWORD(BG_COLOR color = E_BLACK_BG_COLOR);
bool saveOptions(OptionSet &options, OptionSet newOptions);
bool loadOptions(OptionSet &options);

#endif