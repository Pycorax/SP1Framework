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
	
	string maps[] = {"testing", "testing2", "testing3","testing4","testing5","testing6","testing7","testing8"};

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
				game = GAME_OVER;
				break;
			case GAME_OVER:
				gameOver(game);
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