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

int main()
{
	init();      // initialize your variables
	GAMESTATE game = E_MAIN_MENU;
	
	Loadables loads(0,3,0);
	OptionSet options; //Initialised to default values in "options.h"

	loadOptions(options);
	
	//Controls maps & map order in normal mode
	const size_t NUM_OF_MAPS = 11;
	string maps[NUM_OF_MAPS] = 
	{
		"LEVEL1",
		"LEVEL3",
		"testing",
		"testing2",
		"testing3",
		"testing4",
		"testing5",
		"testing6",
		"testing7",
		"testing8",
		"testingA"
	};

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
				highScoreBoard();
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
			case E_CUSTOM_GAME_GUIDE:
				customGameGuide(game);
				break;
		}
	}
	
	return 0;
}