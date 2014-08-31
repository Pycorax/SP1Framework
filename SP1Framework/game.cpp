// This is the main file for the game logic and function
//
//
#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include "Framework\console.h"
#include "Framework\timer.h"
#include "globals.h"
#include "userInterface.h"
#include "scorePoints.h"
#include "gameStage.h"
#include "otherHelperFunctions.h"
#include <Windows.h>
#include "highscore.h"

using std::ostringstream;
using std::cout;
using std::endl;

//Globals
COORD consoleSize = {120, 60};
COORD defaultConsoleSize = consoleSize;
const unsigned char FPS = 7;					// FPS of this game
const unsigned int frameTime = 1000 / FPS;		// time for each frame
StopWatch g_timer;								// Timer function to keep track of time and the frame rate
double elapsedTime;
double deltaTime;
bool keyPressed[E_MAX_KEYS];

void init()
{
	extern COORD consoleSize;
	extern double elapsedTime;

    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"PacGun");

	// Sets the console size in the form x,y
	newSetConsoleSize(consoleSize);

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

void clearInput()
{
	keyPressed[E_UP_KEY] = false;
	keyPressed[E_DOWN_KEY] = false;
	keyPressed[E_LEFT_KEY] = false;
	keyPressed[E_RIGHT_KEY] = false;
	keyPressed[E_ESCAPE_KEY] = false;
	keyPressed[E_SPACE_KEY] = false;
}

void update(double dt, Map &currentMap, Pacman &player)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	Ghost *ghostPtr = NULL;
	bool gotoNextLevel = false;
	
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
		Beep(1000, 100);
	}

	//Power-ups Eating
	if(currentMap.processedMap[player.coord.Y][player.coord.X] == 'H')
	{
		currentMap.processedMap[player.coord.Y][player.coord.X] = ' ';
		player.lives += 1;
		Beep(1000, 100);
	}

	if(currentMap.processedMap[player.coord.Y][player.coord.X] == 's')
	{
		currentMap.processedMap[player.coord.Y][player.coord.X] = ' ';

		currentMap.bulletSpeed = 3;
	}

	if(currentMap.processedMap[player.coord.Y][player.coord.X] == 'd')
	{
		currentMap.processedMap[player.coord.Y][player.coord.X] = ' ';
		currentMap.bulletDamage = 2;
		Beep(1000, 100);
	}
	
	//Bullet shooting
	if(currentMap.shot == NULL)
	{
		if(keyPressed[E_SPACE_KEY])
		{
			currentMap.shot = new Bullet(player, currentMap.bulletDamage,currentMap.bulletSpeed);
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
			if(currentMap.ghostStorage[i].isHitByBullet(*(currentMap.shot), currentMap) && currentMap.ghostStorage[i].isAlive())
			{
				currentMap.ghostStorage[i].health -= currentMap.shot->damage;
				currentMap.ghostStorage[i].respawnTime = time(NULL) + currentMap.ghostStorage[i].timeToRespawn;
				currentMap.scorePoints += g_SCORE_PER_HIT;
				printTile(currentMap.processedMap[currentMap.ghostStorage[i].coord.Y][currentMap.ghostStorage[i].coord.X], currentMap.ghostStorage[i].coord);

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
		if(currentMap.ghostStorage[i].isAlive())
		{
			//Checks if player touched the ghost before ghosts move
			if(player.isHitByGhost(currentMap.ghostStorage[i]))
			{
				player.lives -= currentMap.ghostStorage[i].damage;
				player.coord = currentMap.startPos;
				currentMap.scorePoints += g_SCORE_PER_DEATH;
			}

			//Moves Ghosts
			currentMap.ghostStorage[i].move(currentMap);

			//Checks if player touched the ghost after ghosts move
			if(player.isHitByGhost(currentMap.ghostStorage[i])) 
			{
				player.lives -= currentMap.ghostStorage[i].damage;
				player.coord = currentMap.startPos;
				currentMap.scorePoints += g_SCORE_PER_DEATH;

				if(currentMap.scorePoints >= currentMap.minScore && player.isAlive())
				{
					gotoNextLevel = true;
				}
			}

			if(currentMap.shot != NULL)
			{
				//Check for ghost collision again after ghosts move
				if(currentMap.ghostStorage[i].isHitByBullet(*(currentMap.shot), currentMap) && currentMap.shot->collided == false)
				{
					currentMap.ghostStorage[i].health -= currentMap.shot->damage;
					currentMap.ghostStorage[i].respawnTime = time(NULL) + currentMap.ghostStorage[i].timeToRespawn;
					currentMap.scorePoints += g_SCORE_PER_HIT;
					printTile(currentMap.processedMap[currentMap.ghostStorage[i].oldCoord.Y][currentMap.ghostStorage[i].oldCoord.X], currentMap.ghostStorage[i].oldCoord);

					currentMap.shot->collided = true;
					break;
				}
				if(currentMap.shot->collided && currentMap.shot->firstMove)
				{
					delete currentMap.shot;
					currentMap.shot = NULL;
				}
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

	if(gotoNextLevel)
	{
		currentMap.levelState = E_WIN;
	}

	if (keyPressed[E_ESCAPE_KEY])
	{
		currentMap.levelState = E_PAUSE;
	}
}

void render(Map &currentMap, Pacman &player, Loadables loads, bool isCustom)
{
	//Print HUD
	colour(BACKGROUND_GREEN);
	printScore(currentMap.scorePoints, currentMap.minScore);
	printPellets(currentMap.pellets);
	printLives(player.lives);
	if(!isCustom)
	{
		printCumulativeScore(currentMap.scorePoints, loads.cumulativeScore);
	}

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

		else
		{
			Beep(300, 100);
		}
	}
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void levelLoop(string mapName, GAMESTATE &game, unsigned int level, Loadables &loads)
{
	//Load & Print Map
	loadingScreen(mapName);

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
		//Level start screen here
		startScreen(mapName);
		Sleep(1500);
		cls();

		consoleSize.X = currentMap.processedMap[0].size() * TILE_WIDTH;
		consoleSize.Y = currentMap.processedMap.size() * TILE_HEIGHT + HUD_OFFSET * TILE_HEIGHT;

		newSetConsoleSize(consoleSize);

		//Print static HUD
		printHUDBackground();

		currentMap.renderMap();

		//Print HUD background
		colour(BACKGROUND_GREEN);
		printHUDBackground();
		gotoXY(20,0);
		printLevelName(mapName);
		printLevel(level);

		Pacman player(currentMap, loads.playerLives);
		Bullet shoot(player, currentMap.bulletDamage,currentMap.bulletSpeed);

		g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
		while (currentMap.levelState == E_PLAYING || currentMap.levelState == E_MIN_SCORE_HIT || currentMap.levelState == E_PAUSE)      // run this loop until user wants to quit 
		{        
			getInput();												// get keyboard input
			update(g_timer.getElapsedTime(), currentMap, player);   // update the game
			render(currentMap, player, loads);
			g_timer.waitUntil(frameTime);						// Frame rate limiter. Limits each frame to a specified time in ms.
			if(currentMap.levelState == E_PAUSE)
			{
				cls();
				gotoXY(0,0);
				colour(BACKGROUND_GREEN);
				//TODO: Pause menu here
				if(!pauseMenu(currentMap.levelState, loads))
				{
					colour(FOREGROUND_GREEN);
					cls();
					currentMap.renderMap();

					//Print HUD background
					colour(BACKGROUND_GREEN);
					printHUDBackground();
					gotoXY(20,0);
					printLevelName(mapName);
				}
			}
		}

		//Saves info
		loads.playerLives = player.lives;
		loads.cumulativeScore += currentMap.scorePoints;
		loads.level = level + 1; //Sets level after this to be the one to load

		colour(FOREGROUND_GREEN);
		cls();

		
		switch(currentMap.levelState)
		{
			case E_LOSS:
				loseScreen();
				highScoreBoard(currentMap.scorePoints);
				game = E_MAIN_MENU;
				break;
			case E_WIN:
				victoryScreen();
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

void customLevelLoop(string mapName, Loadables loads)
{
	//Load & Print Map
	loadingScreen(mapName);

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
		//Level start screen here
		startScreen(mapName);
		Sleep(1500);
		cls();

		consoleSize.X = currentMap.processedMap[0].size() * TILE_WIDTH;
		consoleSize.Y = currentMap.processedMap.size() * TILE_HEIGHT + HUD_OFFSET * TILE_HEIGHT;

		newSetConsoleSize(consoleSize);

		//Print static HUD
		printHUDBackground();

		currentMap.renderMap();

		//Print HUD background
		colour(BACKGROUND_GREEN);
		printHUDBackground();
		gotoXY(20,0);
		printLevelName(mapName);

		Pacman player(currentMap, loads.playerLives);
		Bullet shoot(player, currentMap.bulletDamage,currentMap.bulletSpeed);

		g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
		while (currentMap.levelState == E_PLAYING || currentMap.levelState == E_MIN_SCORE_HIT || currentMap.levelState == E_PAUSE)      // run this loop until user wants to quit 
		{        
			getInput();												// get keyboard input
			update(g_timer.getElapsedTime(), currentMap, player);   // update the game
			render(currentMap, player, loads, true);
			g_timer.waitUntil(frameTime);						// Frame rate limiter. Limits each frame to a specified time in ms.
			if(currentMap.levelState == E_PAUSE)
			{
				cls();
				gotoXY(0,0);
				colour(BACKGROUND_GREEN);
				//TODO: Pause menu here
				if(!pauseMenu(currentMap.levelState, loads, true))
				{
					colour(FOREGROUND_GREEN);
					cls();
					currentMap.renderMap();

					//Print HUD background
					colour(BACKGROUND_GREEN);
					printHUDBackground();
					gotoXY(20,0);
					printLevelName(mapName);
				}
			}
		}

		colour(FOREGROUND_GREEN);
		cls();


		switch(currentMap.levelState)
		{
			case E_LOSS:
				loseScreen();
				break;
			case E_WIN:
				victoryScreen();
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
