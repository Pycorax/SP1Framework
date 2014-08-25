#include "gameStage.h"
#include <iostream>
#include "maps.h"
#include "game.h"
#include <conio.h>
#include "Framework/console.h"
#include <string>
#include "userInterface.h"
#include "saves.h"

extern COORD consoleSize;

using std::cout;
using std::cin;
using std::endl;
using std::string;

void mainMenu(gameState &game)
{
	colour (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cls();

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

void gameLoop(string maps[], gameState &game, unsigned int level)
{
	for(size_t currentLevel = level; currentLevel < sizeof(maps); ++currentLevel)
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

//Pause Menu stuff
void saveMenu()
{
	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t SAVE_MENU_TITLE = 8;
	string saveMenuTitle[SAVE_MENU_TITLE] = 
	{
		":'######:::::'###::::'##::::'##:'########:::::'######::::::'###::::'##::::'##:'########:",
		"'##... ##:::'## ##::: ##:::: ##: ##.....:::::'##... ##::::'## ##::: ###::'###: ##.....::",
		" ##:::..:::'##:. ##:: ##:::: ##: ##:::::::::: ##:::..::::'##:. ##:: ####'####: ##:::::::",
		". ######::'##:::. ##: ##:::: ##: ######:::::: ##::'####:'##:::. ##: ## ### ##: ######:::",
		":..... ##: #########:. ##:: ##:: ##...::::::: ##::: ##:: #########: ##. #: ##: ##...::::",
		"'##::: ##: ##.... ##::. ## ##::: ##:::::::::: ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::",
		". ######:: ##:::: ##:::. ###:::: ########::::. ######::: ##:::: ##: ##:::: ##: ########:",
		":......:::..:::::..:::::...:::::........::::::......::::..:::::..::..:::::..::........::"
	};

	int saveMenuTitlePrintSpot = consoleSize.X/2 - saveMenuTitle[0].length()/2;

	for(size_t i = 0; i < SAVE_MENU_TITLE; ++i)
	{
		gotoXY(saveMenuTitlePrintSpot, 6 + i);
		cout << saveMenuTitle[i];
	}

	const size_t SAVE_MENU_OPTIONS = 8;
	string saveMenuOptions[SAVE_MENU_OPTIONS] =
	{
		" __________________ ",
		"|                  |", //Total Length 20
		"|                  |",
		"|  (1) Return      |",
		"|  (2) Load Game   |",
		"|  (3) Return      |",
		"|                  |",
		"|__________________|"
	};

	int saveMenuOptionsPrintSpot = consoleSize.X/2 - saveMenuOptions[0].length()/2;

	for(size_t i = 0; i < SAVE_MENU_OPTIONS; ++i)
	{
		gotoXY(saveMenuOptionsPrintSpot, 17 + i);
		cout << saveMenuOptions[i];
	}

	gotoXY(60, 17 + SAVE_MENU_OPTIONS);

	
	/*while(levelState == MAIN_MENU)
	{
		switch(getch())
		{
		case'1':
			levelState = GAME;
			break;
		default:
			levelState = MAIN_MENU;
			break;
		}
	}*/
}

void loadMenu(gameState &game, unsigned int &level) //WIP
{
	vector<string> listOfLevels;
	findSaveFiles(listOfLevels);

	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t LOAD_MENU_TITLE = 8;
	string loadMenuTitle[LOAD_MENU_TITLE] = 
	{
		"'##::::::::'#######:::::'###::::'########::::::'######::::::'###::::'##::::'##:'########:",
		"##:::::::'##.... ##:::'## ##::: ##.... ##::::'##... ##::::'## ##::: ###::'###: ##.....::",
		"##::::::: ##:::: ##::'##:. ##:: ##:::: ##:::: ##:::..::::'##:. ##:: ####'####: ##:::::::",
		"##::::::: ##:::: ##:'##:::. ##: ##:::: ##:::: ##::'####:'##:::. ##: ## ### ##: ######:::",
		"##::::::: ##:::: ##: #########: ##:::: ##:::: ##::: ##:: #########: ##. #: ##: ##...::::",
		"##::::::: ##:::: ##: ##.... ##: ##:::: ##:::: ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::",
		"########:. #######:: ##:::: ##: ########:::::. ######::: ##:::: ##: ##:::: ##: ########:",
		"........:::.......:::..:::::..::........:::::::......::::..:::::..::..:::::..::........::"
	};

	int loadMenuTitlePrintSpot = consoleSize.X/2 - loadMenuTitle[0].length()/2;

	for(size_t i = 0; i < LOAD_MENU_TITLE; ++i)
	{
		gotoXY(loadMenuTitlePrintSpot, 6 + i);
		cout << loadMenuTitle[i];
	}

	const size_t LOAD_MENU_OPTIONS_HEAD = 4;
	string loadMenuOptionsHead[LOAD_MENU_OPTIONS_HEAD] =
	{
		" __________________ ",
		"|                  |", //Total Length 20
		"|                  |",
		"|  (1) Return      |"
	};

	const size_t LOAD_MENU_OPTIONS_FOOT = 2;
	string loadMenuOptionsFoot[LOAD_MENU_OPTIONS_FOOT] =
	{
		"|                  |",
		"|__________________|"
	};

	int loadMenuOptionsPrintSpot = consoleSize.X/2 - loadMenuOptionsHead[0].length()/2;
	int loadMenuOptionsHeadLength = loadMenuOptionsHead[0].length();

	for(size_t i = 0; i < LOAD_MENU_OPTIONS_HEAD; ++i)
	{
		gotoXY(loadMenuOptionsPrintSpot, 17 + i);
		cout << loadMenuOptionsHead[i];
	}

	size_t numOfSaves = 0;
	bool saveFilesPresent = false;
	for(; numOfSaves < listOfLevels.size(); ++numOfSaves)
	{
		gotoXY(loadMenuOptionsPrintSpot, 17 + LOAD_MENU_OPTIONS_HEAD + numOfSaves);
		cout << "|  (" << numOfSaves + 2 << ") " << listOfLevels[numOfSaves];
		gotoXY(loadMenuOptionsPrintSpot + loadMenuOptionsHeadLength, 17 + LOAD_MENU_OPTIONS_HEAD + numOfSaves);
		cout << "|";
		
		saveFilesPresent = true;
	}

	int saveFilesToPrint = numOfSaves;

	if(!saveFilesPresent)
	{
		gotoXY(loadMenuOptionsPrintSpot, 17 + LOAD_MENU_OPTIONS_HEAD + numOfSaves);
		cout << "|                  |";
		gotoXY(loadMenuOptionsPrintSpot, 17 + LOAD_MENU_OPTIONS_HEAD + numOfSaves + 1);
		cout << "|     No Saves     |";
		saveFilesToPrint = 2;
	}

	for(size_t i = 0; i < LOAD_MENU_OPTIONS_FOOT; ++i)
	{
		gotoXY(loadMenuOptionsPrintSpot, 17 + LOAD_MENU_OPTIONS_HEAD + saveFilesToPrint + i);
		cout << loadMenuOptionsFoot[i];
	}

	gotoXY(consoleSize.X/2, 17 + LOAD_MENU_OPTIONS_HEAD + saveFilesToPrint + LOAD_MENU_OPTIONS_FOOT);

	while(game == LOAD_MENU)
	{
		char input = getch();

		if (input == '1')
		{
			game = MAIN_MENU;
		}
		else if (numOfSaves > 0)
		{
			if (input > '1' && input < '1' + numOfSaves)
			{
				loadGame(level, listOfLevels[input - 2]);
			}
		}
		else
		{
			game = LOAD_MENU;
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