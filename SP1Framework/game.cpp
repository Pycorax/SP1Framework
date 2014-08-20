// This is the main file for the game logic and function
//
//
#include "game.h"
#include "characters.h"

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD consoleSize;

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

	// wipe old character
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	player.undraw(currentMap);
    
	// render character
    colour(0x0C);
    player.draw();
    
	// wipe ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].undraw(currentMap);
	}
	// render ghosts
	for(size_t i = 0; i < currentMap.ghostStorage.size(); ++i)
	{
		currentMap.ghostStorage[i].draw();
	}
}
