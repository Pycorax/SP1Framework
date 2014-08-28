#include "gameStage.h"
#include <iostream>
#include "maps.h"
#include "game.h"
#include <conio.h>
#include "Framework/console.h"
#include <string>
#include "userInterface.h"

extern COORD consoleSize;
extern COORD defaultConsoleSize;

using std::cout;
using std::cin;
using std::endl;
using std::string;

void mainMenu(gameState &game)
{
	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t MAIN_MENU_TITLE = 8;
	string mainMenuTitle[MAIN_MENU_TITLE] = 
	{
		"'########:::::'###:::::'######:::'######:::'##::::'##:'##::: ##:",
		" ##.... ##:::'## ##:::'##... ##:'##... ##:: ##:::: ##: ###:: ##:", 
		" ##:::: ##::'##:. ##:: ##:::..:: ##:::..::: ##:::: ##: ####: ##:", //Total Length = 64
		" ########::'##:::. ##: ##::::::: ##::'####: ##:::: ##: ## ## ##:",
		" ##.....::: #########: ##::::::: ##::: ##:: ##:::: ##: ##. ####:",
		" ##:::::::: ##.... ##: ##::: ##: ##::: ##:: ##:::: ##: ##:. ###:",
		" ##:::::::: ##:::: ##:. ######::. ######:::. #######:: ##::. ##:",
		"..:::::::::..:::::..:::......::::......:::::.......:::..::::..::"
	};

	int mainMenuTitlePrintSpot = consoleSize.X/2 - mainMenuTitle[0].length()/2;

	for(size_t i = 0; i < MAIN_MENU_TITLE; ++i)
	{
		gotoXY(mainMenuTitlePrintSpot, 6 + i);
		cout << mainMenuTitle[i];
	}

	const size_t MAIN_MENU_OPTIONS = 9;
	string mainMenuOptions[MAIN_MENU_OPTIONS] =
	{
		" __________________ ",
		"|                  |", //Total Length 20
		"|                  |",
		"|  (1) Start Game  |",
		"|  (2) Load Game   |",
		"|  (3) Exit Game   |",
		"|  (4) Game Guide  |",
		"|                  |",
		"|__________________|"
	};

	int mainMenuOptionsPrintSpot = consoleSize.X/2 - mainMenuOptions[0].length()/2;

	for(size_t i = 0; i < MAIN_MENU_OPTIONS; ++i)
	{
		gotoXY(mainMenuOptionsPrintSpot, 17 + i);
		cout << mainMenuOptions[i];
	}

	gotoXY(60, 17 + MAIN_MENU_OPTIONS);
	
	while(game == MAIN_MENU)
	{
		switch(getch())
		{
		case'1':
			game = GAME;
			break;
		case'2':
			game = LOAD_MENU;
			break;
		case'3':
			game = QUIT_MENU;
			break;
		case'4':
			game = GAME_GUIDE;
			break;
		default:
			game = MAIN_MENU;
			break;
		}
	}
}

void gameGuide(gameState &game)
	{
		//consoleSize = consoleSize;
		//setConsoleSize;
		colour(FOREGROUND_GREEN | FOREGROUND_RED);
		const size_t GAME_GUIDE_MENU = 8;
		string gameguideMenu[GAME_GUIDE_MENU] =
		{
			":'######::::::'###::::'##::::'##:'########:::::'######:::'##::::'##:'####:'########::'########:",
			"'##... ##::::'## ##::: ###::'###: ##.....:::::'##... ##:: ##:::: ##:. ##:: ##.... ##: ##.....::",
			" ##:::..::::'##:. ##:: ####'####: ##:::::::::: ##:::..::: ##:::: ##:: ##:: ##:::: ##: ##:::::::",
			" ##::'####:'##:::. ##: ## ### ##: ######:::::: ##::'####: ##:::: ##:: ##:: ##:::: ##: ######:::",
			" ##::: ##:: #########: ##. #: ##: ##...::::::: ##::: ##:: ##:::: ##:: ##:: ##:::: ##: ##...::::",
			" ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::::: ##::: ##:: ##:::: ##:: ##:: ##:::: ##: ##:::::::",
			". ######::: ##:::: ##: ##:::: ##: ########::::. ######:::. #######::'####: ########:: ########:",
			":......::::..:::::..::..:::::..::........::::::......:::::.......:::....::........:::........::"
		};

		const size_t GAME_INSTRUCTIONS = 30;
		string gameInstructions[GAME_INSTRUCTIONS] =
		{
			"HOW TO PLAY?",
			"	1: Use Arrow Keys to move the pacman around",
			"	2: Collect all pellets or reach minimum points to go to the next level",
			"	3: Kill Ghosts or collect pellets to gain points",
			"	4: Try not to let ghosts touch you",
			"	                                  ",
			"Introductions    ",
			"                    ",
			"	Ghosts:          ",
			"	   /1\\  Health: 1",
			"	   o-o  Damage: 1",
			"	   VVV           ",
			"                    ",
			"	   /2\\  Health: 2",
			"	   o-o  Damage: 1",
			"	   VVV           ",
			"                    ",
			"	   [3]  Health: 3",
			"	   o-o  Damage: 1",
			"	   VVV           ",
			"                    ",
			"	Pacman:          ",
			"	   ___ ",
			"	   (*=  Health: 1",
			"                    ",
			"	Bullets:         ",
			"	   =>>  Damage: 1",


		};

		int gameguideprintSpots = consoleSize.X/2 - gameguideMenu[0].length()/2;

		for(size_t a = 0; a < GAME_GUIDE_MENU; ++a)
		{
			gotoXY(gameguideprintSpots, 2 + a);
			cout << gameguideMenu[a];
		}

		//int gameinstructionsprintSpots = consoleSize.X/2 - gameInstructions[0].length()/2;

		for(size_t b = 0; b < GAME_INSTRUCTIONS; ++b)
		{
			gotoXY(13, 10 + b);
			cout << gameInstructions[b] << endl;
		}

		system("pause");

		game = MAIN_MENU;
	}


void gameLoop(string maps[], gameState &game)
{
	for(size_t currentLevel = 0; currentLevel < sizeof(maps); ++currentLevel)
	{
		if(game == GAME)
		{
			levelLoop(maps[currentLevel], game);
		} 
		else
		{
			break;
		}
	}
}

bool quit(gameState &game)
{
	char input;

	do 
	{
		cout << "Are you sure you want to quit? (Y/N)"<< endl;
		input = toupper(getch());
	}
	while (!(input == 'Y' || input == 'N'));
	
	if(input == 'Y')
	{
		game = EXIT;
		return true;
	}
	else if(input == 'N')
	{
		game = MAIN_MENU;
		return false;
	}

	return false;
}

void victoryScreen()
{
	const int b = 13;
				string victoryScreen[b] =
				{
					"'##::::'##:'####::'######::'########::'#######::'########::'##:::'##:",
					" ##:::: ##:. ##::'##... ##:... ##..::'##.... ##: ##.... ##:. ##:'##::",
					" ##:::: ##:: ##:: ##:::..::::: ##:::: ##:::: ##: ##:::: ##::. ####:::",
					" ##:::: ##:: ##:: ##:::::::::: ##:::: ##:::: ##: ########::::. ##::::",
					". ##:: ##::: ##:: ##:::::::::: ##:::: ##:::: ##: ##.. ##:::::: ##::::",
					":. ## ##:::: ##:: ##::: ##:::: ##:::: ##:::: ##: ##::. ##::::: ##::::",
					"::. ###::::'####:. ######::::: ##::::. #######:: ##:::. ##:::: ##::::",
					"                                                                     ",
					"                                                                     ",
					"               CONGRATULATIONS ON COMPLETING THIS LEVEL                 "
				};

				colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				cls();
				for(int a = 0; a < b; ++a)
				{
					gotoXY(consoleSize.X/2 - victoryScreen[a].length()/2, 10 + a);
					cout << victoryScreen[a];
				}
				Sleep(5000);
}

void loseScreen()
{
	const int b = 13;
		string loseScreen[b] =
		{
			"'########::::'###::::'####:'##:::::::'########:'########::",
			" ##.....::::'## ##:::. ##:: ##::::::: ##.....:: ##.... ##:",
			" ##::::::::'##:. ##::: ##:: ##::::::: ##::::::: ##:::: ##:",
			" ######:::'##:::. ##:: ##:: ##::::::: ######::: ##:::: ##:",
		    " ##...:::: #########:: ##:: ##::::::: ##...:::: ##:::: ##:",
			" ##::::::: ##.... ##:: ##:: ##::::::: ##::::::: ##:::: ##:",
			" ##::::::: ##:::: ##:'####: ########: ########: ########::",
			"                                                          ",
			"                                                          ",
			"             YOU FAILED TO COMPLETE THE GAME              "
		};

		colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cls();
		for(int a = 0; a < b; ++a)
		{
			gotoXY(consoleSize.X/2 - loseScreen[a].length()/2, 10 + a);
			cout << loseScreen[a];
		}

		Sleep(5000);
}