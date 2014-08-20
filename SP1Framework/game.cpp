// This is the main file for the game logic and function
//
//
#include "game.h"


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD oldCharLocation;
COORD consoleSize;
direction charDirection;
COORD ghostLocation;
direction ghostDirection;
Pacman player();

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"PacGun");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

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
}

void update(double dt, vector<vector<char>> processedMap)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	oldCharLocation = charLocation;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
		if(processedMap[(charLocation.Y - TILE_HEIGHT - HUD_OFFSET)/TILE_HEIGHT][(charLocation.X)/TILE_WIDTH] != '#')
		{
			Beep(1440, 30);
			charLocation.Y -= TILE_HEIGHT;
			charDirection = UP;
		}
    }
	else if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		if(processedMap[(charLocation.Y - HUD_OFFSET)/TILE_HEIGHT][(charLocation.X - TILE_WIDTH)/TILE_WIDTH] != '#')
		{
			Beep(1440, 30);
			charLocation.X -= TILE_WIDTH;
			charDirection = LEFT;
		}
	}
    else if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		if(processedMap[(charLocation.Y + TILE_HEIGHT - HUD_OFFSET)/TILE_HEIGHT][(charLocation.X)/TILE_WIDTH] != '#')
		{
			Beep(1440, 30);
			charLocation.Y += TILE_HEIGHT;
			charDirection = DOWN;
		}
    }
    else if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if(processedMap[(charLocation.Y - HUD_OFFSET)/TILE_HEIGHT][(charLocation.X + TILE_WIDTH)/TILE_WIDTH] != '#')
		{
			Beep(1440, 30);
			charLocation.X += TILE_WIDTH;
			charDirection = RIGHT;
		}
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
        g_quitGame = true;
	}
}

void render(vector<vector<char>> &processedMap)
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
	printTile(processedMap[oldCharLocation.Y/TILE_HEIGHT - HUD_OFFSET/TILE_HEIGHT][oldCharLocation.X/TILE_WIDTH], oldCharLocation);
    // render character
    gotoXY(charLocation);
    colour(0x0C);
    printPlayer(charLocation, charDirection);

    // render character
    gotoXY(ghostLocation);
    colour(0x0D);
    //printPlayer(ghostLocation, ghostDirection);
}
