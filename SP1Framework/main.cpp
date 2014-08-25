// This is the main file to hold everthing together

#include "gameStage.h"
#include "game.h"
#include <vector>
#include <string>
#include "Framework/console.h"

using std::string;
using std::vector;

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
	gameState game = MAIN_MENU;
	
	const size_t NUM_OF_MAPS = 8;
	string maps[NUM_OF_MAPS] = {"testing", "testing2", "testing3","testing4","testing5","testing6","testing7","testing8"};

	while(game != EXIT)
	{
		cls();
		switch(game)
		{
			case MAIN_MENU:
				mainMenu(game);
				break;
			case GAME:
				gameLoop(maps, NUM_OF_MAPS, game);
				game = MAIN_MENU;
				break;
			case QUIT_MENU:
				if(quit(game))
				{
					shutdown(); // do clean up, if any. free memory.
				}
				break;
		}
	}
	
	return 0;
}