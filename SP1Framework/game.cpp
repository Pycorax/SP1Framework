// This is the main file for the game logic and function
//
//
#include "game.h"
#include "characters.h"
#include "maps.h"

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
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
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
}

void update(double dt, Map &currentMap, Pacman &player)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	
	player.oldCoord = player.coord;

     // Updating the location of the character based on the key press
	if (keyPressed[K_UP])
    {
		player.direct = UP;
		player.move(currentMap);

    }
    else if (keyPressed[K_LEFT])
    {
		player.direct = LEFT;
		player.move(currentMap);
		
	}
    else if (keyPressed[K_DOWN])
    {
		player.direct = DOWN;
		player.move(currentMap);
    }
    else if (keyPressed[K_RIGHT])
    {
		player.direct = RIGHT;
		player.move(currentMap);
	}

	//Pellet eating
	if(currentMap.processedMap[player.coord.Y][player.coord.X] == '.')
	{
		currentMap.processedMap[player.coord.Y][player.coord.X] = ' ';
		currentMap.scorePoints += 100;
	}

	//Bullet shooting
	if(currentMap.shot == NULL)
	{
		if(keyPressed[K_SPACE])
		{
			currentMap.shot = new Bullet(player);
			currentMap.shot->move(currentMap);
		}	
	}
	else if(currentMap.shot->collided == false)
	{
		currentMap.shot->move(currentMap);
		//TODO: Bug fix
		//Check before moving else the check for wall collision will give an error when shooting beside the wall at the wall

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

		//Check for wall collision
		if(currentMap.processedMap[currentMap.shot->coord.Y][currentMap.shot->coord.X] == '#')
		{
			currentMap.shot->collided = true;
		}
	}
	else if(currentMap.shot->collided) //Prevent immediate deletion upon collision to allow bullet to be undraw() first
	{
		delete currentMap.shot;
		currentMap.shot = NULL;
	}
	
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
        g_quitGame = true;
	}

	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].move(currentMap);
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

	colour(BACKGROUND_RED);
	
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
    player.draw();

	//Wipe old Ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].undraw(currentMap);
	}

	//Render Ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].draw();
	}

	//Render Bullet & Wipe old Bullets
	if(currentMap.shot != NULL)
	{
		currentMap.shot->undraw(currentMap);

		if(currentMap.shot->collided == false)
		{
			currentMap.shot->draw();
		}
	}
}
