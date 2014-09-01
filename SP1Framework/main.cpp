// This is the main file to hold everthing together

#include "gameStage.h"
#include "game.h"
#include <string>
#include "Framework/console.h"
#include "saves.h"
#include "otherHelperFunctions.h"
#include "options.h"
#include "highscore.h"

using std::string;

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
	GAMESTATE game = E_MAIN_MENU;
	
	Loadables loads(0,3,0);
	OptionSet options; //Initialised to default values in "options.h"

	loadOptions(options);
	
	const size_t NUM_OF_MAPS = 8;
	string maps[NUM_OF_MAPS] = {"testing", "testing2", "testing3","testing4","testing5","testing6","testing7","testing8"};

	while(game != E_EXIT)
	{
		flushInputBuffer();
		cls();
		switch(game)
		{
			case E_MAIN_MENU:
				loads.level = 0;
				loads.playerLives = 3;
				loads.cumulativeScore = 0;
				mainMenu(game);
				break;
			case E_GAME:
				gameLoop(maps, NUM_OF_MAPS, game, loads, options);
				break;
			case E_LOAD_SAVES:
				loadMenu(game, loads);
				break;
			case E_LOAD_CUSTOM:
				loadCustomLevelMenu(game, options);
				break;
			case E_DELETE_SAVES:
				deleteMenu(game);
				break;
			case E_HIGH_SCORES:
				highScoreBoard(-1, "level_1");
				game = E_MAIN_MENU;
				break;
			case E_OPTIONS_MENU:
				optionsMenu(game, options);
				game = E_MAIN_MENU;
				break;
			case E_ABOUT_SCREEN:
				aboutScreen();
				game = E_MAIN_MENU;
				break;
			case E_QUIT_MENU:
				if(quit(game))
				{
					shutdown(); // do clean up, if any. free memory.
				}
				break;
			case E_GAME_GUIDE:
				 gameGuide(game);
				 break;
		}
	}
	
	return 0;
}