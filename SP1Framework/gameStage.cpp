#include "gameStage.h"
#include <iostream>
#include "maps.h"
#include "game.h"
#include <conio.h>
#include "Framework/console.h"
#include <string>
#include "userInterface.h"

extern COORD consoleSize;

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

	const size_t MAIN_MENU_OPTIONS = 8;
	string mainMenuOptions[MAIN_MENU_OPTIONS] =
	{
		" __________________ ",
		"|                  |", //Total Length 20
		"|                  |",
		"|  (1) Start Game  |",
		"|  (2) Load Game   |",
		"|  (3) Exit Game   |",
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
		default:
			game = MAIN_MENU;
			break;
		}
	}
}

void gameOver(gameState &game)
{
	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t GAME_OVER_TITLE = 7;
	string gameOverTitle[GAME_OVER_TITLE] = 
	{
		" ' #######:::::::' #::::: ###:::. ###: ########::::::' #######::: ##:::::::::: ##: ########: ########:::::",
		" ##.:::: ##::::' ## ##::: ####:. ####: ##:: :::::::: ##:::::: ##:: ##:::::::: ##:: ##::::::: ##::::: ##:::", 
		" ##:::: ::::::' ##:. ##:: ##:## ## ##: ##::::::::::: ##:::::: ##::: ##:::::: ##::: ##::::::: ##::::: ##:::", 
		" ##::: ######: ##:::. ##: ##::.#.: ##: ########::::: ##:::::: ##:::: ##:::: ##:::: ########: ########:::::",
		" ##.:::: ## :: #########: ##:::::: ##: ##::::::::::: ##:::::: ##::::: ##:: ##::::: ##::::::: ####:::::::::",
		" ##::::: ##::: ##:::: ##: ##:::::: ##: ##::::::::::: ##:::::: ##:::::: ## ##:::::: ##::::::: ##:: ##::::::",
		"..########:::: ##:::: ##: ##:::::: ##: ########::::::: #######::::::::: ###::::::: ########: ##::::: ##:::",
	};

	int gameOverTitlePrintSpot = consoleSize.X/2 - gameOverTitle[0].length()/2;

	for(size_t i = 0; i < GAME_OVER_TITLE; ++i)
	{
		gotoXY(gameOverTitlePrintSpot, 6 + i);
		cout << gameOverTitle[i];
	}

	const size_t GAME_OVER_OPTIONS = 8;
	string gameOverOptions[GAME_OVER_OPTIONS] =
	{
		" __________________ ",
		"|                  |", //Total Length 20
		"|                  |",
		"|  (1) Main Menu   |",
		"|  (3) Exit Game   |",
		"|                  |",
		"|__________________|"
	};

	int gameOverOptionsPrintSpot = consoleSize.X/2 - gameOverOptions[0].length()/2;

	for(size_t i = 0; i < GAME_OVER_OPTIONS; ++i)
	{
		gotoXY(gameOverOptionsPrintSpot, 17 + i);
		cout << gameOverOptions[i];
	}

	gotoXY(60, 17 + GAME_OVER_OPTIONS);
	
	while(game == GAME_OVER)
	{
		switch(getch())
		{
		case'1':
			game = MAIN_MENU;
			break;
		case'2':
			game = QUIT_MENU;
			break;
		default:
			game = GAME_OVER;
			break;
		}
	}

}

void gameLoop(string maps[], gameState &game)
{
	for(size_t currentLevel = 0; currentLevel < sizeof(maps); ++currentLevel)
	{
		//TODO: Add a level splash screen
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