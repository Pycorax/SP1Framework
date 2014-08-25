// This is the main file for the game logic and function
//
//
#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include "Framework\console.h"
#include "globals.h"
#include "userInterface.h"
#include "scorePoints.h"

using std::ostringstream;
using std::cout;
using std::endl;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"PacGun");

	// Sets the console size in the form x,y
	ostringstream oss;
	oss << "mode " << consoleSize.X << "," << consoleSize.Y;

	system(oss.str().c_str());

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[E_UP_KEY] = isKeyPressed(VK_UP);
    keyPressed[E_DOWN_KEY] = isKeyPressed(VK_DOWN);
    keyPressed[E_LEFT_KEY] = isKeyPressed(VK_LEFT);
    keyPressed[E_RIGHT_KEY] = isKeyPressed(VK_RIGHT);
    keyPressed[E_ESCAPE_KEY] = isKeyPressed(VK_ESCAPE);
	keyPressed[E_SPACE_KEY] = isKeyPressed(VK_SPACE);
}

void update(double dt, Map &currentMap, Pacman &player)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	Ghost *ghostPtr = NULL;
	
	player.oldCoord = player.coord;

     // Updating the location of the character based on the key press
	if (keyPressed[E_UP_KEY])
    {
		player.direct = E_UP_DIRECTION;
		player.move(currentMap);

    }
    else if (keyPressed[E_LEFT_KEY])
    {
		player.direct = E_LEFT_DIRECTION;
		player.move(currentMap);
		
	}
    else if (keyPressed[E_DOWN_KEY])
    {
		player.direct = E_DOWN_DIRECTION;
		player.move(currentMap);
    }
    else if (keyPressed[E_RIGHT_KEY])
    {
		player.direct = E_RIGHT_DIRECTION;
		player.move(currentMap);
	}

	//Pellet eating
	if(currentMap.processedMap[player.coord.Y][player.coord.X] == '.')
	{
		currentMap.processedMap[player.coord.Y][player.coord.X] = ' ';
		currentMap.scorePoints += g_SCORE_PER_PELLET;
		--currentMap.pellets;
	}

	//Bullet shooting
	if(currentMap.shot == NULL)
	{
		if(keyPressed[E_SPACE_KEY])
		{
			currentMap.shot = new Bullet(player);
			currentMap.shot->move(currentMap);
		}	
	}
	else if(currentMap.shot->collided == false)
	{
		if(!(currentMap.shot->move(currentMap)))
		{
			currentMap.shot->collided = true;
		}

		//Check for ghost collision
		for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
		{
			//TODO: Fix bug.
			//Assume that there are 2 ghosts.
			//Ghost 1 - ghostStorage[1] & is in front of Ghost 2 on the map
			//Ghost 2 - ghostStorage[0] & is behind Ghost 1 on the map
			//If bullet fires thru both of them, Ghost 2 dies instead of Ghost 1
			if(currentMap.ghostStorage[i].isHitByBullet(*(currentMap.shot), currentMap))
			{
				currentMap.shot->collided = true;
				break;
			}
		}

		if(currentMap.shot->collided && currentMap.shot->firstMove)
		{
			delete currentMap.shot;
			currentMap.shot = NULL;
		}
	}
	else if(currentMap.shot->collided) //Prevent immediate deletion upon collision to allow bullet to be undraw() first
	{
		delete currentMap.shot;
		currentMap.shot = NULL;
	}

	//Ghost related code
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		if(currentMap.ghostStorage[i].isAlive()) //Moves all the Ghosts
		{
			currentMap.ghostStorage[i].move(currentMap);

			if(player.isHitByGhost(currentMap.ghostStorage[i])) //Checks if player touched the ghost
			{
				player.lives -= currentMap.ghostStorage[i].damage;
				player.coord = currentMap.startPos;
				currentMap.scorePoints += g_SCORE_PER_DEATH;
			}
		}
		else if (currentMap.ghostStorage[i].respawnTime <= time(NULL)) //Respawns Ghosts
		{
			currentMap.ghostStorage[i].respawn(currentMap);
		}
	}

	//Check level states E.g. Win/Lose conditions
	
	if (player.isAlive())
	{
		if (currentMap.pellets < 1)
		{
			currentMap.levelState = E_WIN;
		}
		else if(currentMap.scorePoints > currentMap.minScore)
		{
			currentMap.levelState = E_MIN_SCORE_HIT;
		}
		else
		{
			currentMap.levelState = E_PLAYING;
		}
	}
	else
	{
		if(currentMap.scorePoints > currentMap.minScore)
		{
			currentMap.levelState = E_WIN;
		}
		else
		{
			currentMap.levelState = E_LOSS;
		}
	}

	if (keyPressed[E_ESCAPE_KEY])
	{
		currentMap.levelState = E_PAUSE;
	}
}

void render(Map &currentMap, Pacman &player)
{
	/*
    // render time taken to calculate this frame
    gotoXY(72, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;
	*/

	//Print HUD background
	colour(BACKGROUND_GREEN);
	for(size_t i = 0; i < HUD_OFFSET; ++i)
	{
		gotoXY(0,i);
		printBlank(consoleSize.X);
	}

	gotoXY(0,0);
	printInterface(currentMap.scorePoints);

	gotoXY(39,0);
	printminScore(currentMap.minScore);

	gotoXY(70,0);
	//printcollectPoints(currentMap.collectedPoints, currentMap.processedMap[1].size(), currentMap.processedMap.size());

	//Wipe old Player
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	player.undraw(currentMap);

	//Render Player
    colour(0x0C);
	if(player.isAlive())
	{
		player.draw();
	}

	//Wipe & Render Ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		if(currentMap.ghostStorage[i].isAlive())
		{
			currentMap.ghostStorage[i].undraw(currentMap);
			currentMap.ghostStorage[i].draw();
		}
	}

	//Render Bullet & Wipe old Bullets
	if(currentMap.shot != NULL)
	{
		if(currentMap.shot->firstMove == false)
		{
			currentMap.shot->undraw(currentMap);
		}
		if(currentMap.shot->collided == false)
		{
			currentMap.shot->draw();
			currentMap.shot->firstMove = false;
		}
	}
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void levelLoop(string mapName, gameState &game)
{
	//Load & Print Map
	//TODO: Spawn loading screen here
	Map currentMap(mapName);

	bool loadMap = true;

	//Check for map errors
	for(size_t i = 0; i < E_MAX_MAP_ERRORS; ++i)
	{
		if(currentMap.validity.error[i])
		{
			loadMap = false;
		}
	}

	if(loadMap)
	{
		currentMap.renderMap();

		Pacman player(currentMap);
		Bullet shoot (currentMap);

		g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
		while (currentMap.levelState == E_PLAYING || currentMap.levelState == E_MIN_SCORE_HIT || currentMap.levelState == E_PAUSE)      // run this loop until user wants to quit 
		{        
			getInput();												// get keyboard input
			update(g_timer.getElapsedTime(), currentMap, player);   // update the game
			render(currentMap, player);
			g_timer.waitUntil(frameTime);						// Frame rate limiter. Limits each frame to a specified time in ms.
			if(currentMap.levelState == E_PAUSE)
			{
				gotoXY(0,0);
				colour(BACKGROUND_GREEN);
				//TODO: Pause menu here
				char input;
				do
				{
					cout << "Do you wish to end the game? (Y/N)";
					input = getch();
					input = toupper(input);
				}
				while(!(input == 'Y' || input == 'N'));

				switch(toupper(getch()))
				{
					case'Y':
						currentMap.levelState = E_LOSS;
						break;
					default:
						currentMap.levelState = E_PLAYING;
						break;
				}
			}
		}

		cls();

		
		switch(currentMap.levelState)
		{
			case E_LOSS:
				game = MAIN_MENU;
				break;
		}
	}
	else
	{
		//PRINT ERROR SCREEN
		gotoXY(0,0);
		cout << "Error(s) loading level" << endl;
		cout << "=============================================" << endl;
		for(size_t i = 0; i < E_MAX_MAP_ERRORS; ++i)
		{
			if(currentMap.validity.error[i])
			{
				cout << currentMap.validity.errorMessages[i] << endl;
			}
			if(currentMap.validity.error[E_MAP_FILE_DOES_NOT_EXIST])
			{
				break;
			}
		}

		cout << endl << endl;
		system("pause");
		cls();
	}
}
