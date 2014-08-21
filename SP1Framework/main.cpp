// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"
#include "gameStage.h"
#include "maps.h"
#include "characters.h"

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 5; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

void gameLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
	gameState game = GAME;

	while(game != EXIT)
	{
		switch(game)
		{
			case MAIN_MENU:
				mainMenu();
				break;
			case GAME:
				gameLoop();
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

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void gameLoop()
{
	//Load & Print Map
	Map currentMap("testing2.map", "testing2.aimap");
	currentMap.renderMap();

	Pacman player(currentMap);
	Bullet shoot (currentMap);

    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();												// get keyboard input
        update(g_timer.getElapsedTime(), currentMap, player);   // update the game
		render(currentMap, player);
        g_timer.waitUntil(frameTime);							// Frame rate limiter. Limits each frame to a specified time in ms.      
	}    
}
