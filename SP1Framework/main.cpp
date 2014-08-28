// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "gameStage.h"
#include "game.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
	gameState game = MAIN_MENU;
	
	string maps[] = {"testingA", "testing2", "testing"};

	while(game != EXIT)
	{
		system("cls");
		switch(game)
		{
			case MAIN_MENU:
				mainMenu(game);
				break;
			case GAME:
				gameLoop(maps, game);
				game = MAIN_MENU;
				break;
			case QUIT_MENU:
				if(quit(game))
				{
					shutdown(); // do clean up, if any. free memory.
				}
				break;
			case GAME_GUIDE:
				 gameGuide(game);
				 break;
		}
	}
	
	return 0;
}