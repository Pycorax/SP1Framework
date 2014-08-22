// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "globals.h"

double elapsedTime;
double deltaTime;
bool keyPressed[E_MAX_KEYS];
COORD consoleSize;
COORD bulletLocation[1];

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"PacGun");

    // Sets the console size in the form x,y
	system("mode 120,60");

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
			if(currentMap.ghostStorage[i].isHitByBullet(*(currentMap.shot)))
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

	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		if(currentMap.ghostStorage[i].isAlive() == false)
		{
			break;
		}
	}
	
    // quits the game if player hits the escape key
    if (keyPressed[E_ESCAPE_KEY])
	{
        g_quitGame = true;
	}

	//Moves all the Ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].move(currentMap);
	}

	//Checks if player touched the ghost
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		if(currentMap.ghostStorage[i].isAlive() && player.isHitByGhost(currentMap.ghostStorage[i]))
		{
			player.lives -= currentMap.ghostStorage[i].damage;
			player.coord = currentMap.startPos;
		}
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

	//Wipe old Player
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	player.undraw(currentMap);

	//Render Player
    colour(0x0C);
	if(player.isAlive())
	{
		player.draw();
	}

	//Wipe old Ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].undraw(currentMap);
	}

	//Render Ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		if(currentMap.ghostStorage[i].isAlive())
		{
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
void levelLoop(string mapName)
{
	//Load & Print Map
	Map currentMap(mapName);
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
