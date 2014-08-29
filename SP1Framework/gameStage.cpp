#include "gameStage.h"
#include <iostream>
#include <fstream>
#include "maps.h"
#include "game.h"
#include <conio.h>
#include "Framework/console.h"
#include <string>
#include "userInterface.h"
#include "otherHelperFunctions.h"
#include "saves.h"
#include "scorePoints.h"


extern COORD consoleSize;
extern COORD defaultConsoleSize;

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;

void mainMenu(GAMESTATE &game)
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
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

	int mainMenuTitlePrintSpot = defaultConsoleSize.X/2 - mainMenuTitle[0].length()/2;

	for(size_t i = 0; i < MAIN_MENU_TITLE; ++i)
	{
		gotoXY(mainMenuTitlePrintSpot, 6 + i);
		cout << mainMenuTitle[i];
	}

	const size_t MAIN_MENU_OPTIONS = 11;
	string mainMenuOptions[MAIN_MENU_OPTIONS] =
	{
		" ___________________",
		"|                   |", //Total Length 20
		"|                   |",
		"|  (1) Start Game   |",
		"|  (2) Load Game    |",
		"|  (3) Del Saves    |",
		"|  (4) High Scores  |",
		"|  (5) Game Guide   |",
		"|  (6) Exit Game    |",
		"|                   |",
		"|___________________|"
	};

	int mainMenuOptionsPrintSpot = defaultConsoleSize.X/2 - mainMenuOptions[0].length()/2;

	for(size_t i = 0; i < MAIN_MENU_OPTIONS; ++i)
	{
		gotoXY(mainMenuOptionsPrintSpot, 17 + i);
		cout << mainMenuOptions[i];
	}

	gotoXY(consoleSize.X/2, 17 + MAIN_MENU_OPTIONS);
	
	while(game == E_MAIN_MENU)
	{
		switch(getch())
		{
		case'1':
			game = E_GAME;
			break;
		case'2':
			game = E_LOAD_MENU;
			break;
		case'3':
			game = E_DELETE_SAVES;
			break;
		case'4':
			game = E_HIGH_SCORES;
			break;
		case'5':
			game = E_GAME_GUIDE;
			break;
		case'6':
			game = E_QUIT_MENU;
			break;
		default:
			game = E_MAIN_MENU;
			break;
		}
	}
}

void gameGuide(GAMESTATE &game)
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
			gotoXY(13, 2 + GAME_GUIDE_MENU + b);
			cout << gameInstructions[b] << endl;
		}

		pressToContinue(GAME_GUIDE_MENU + GAME_INSTRUCTIONS + 5);

		game = E_MAIN_MENU;
	}

void gameOver(GAMESTATE &game)
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	
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
		"|                  |",
		"|  (2) Exit Game   |",
		"|                  |",
		"|__________________|"
	};

	int gameOverOptionsPrintSpot = defaultConsoleSize.X/2 - gameOverOptions[0].length()/2;

	for(size_t i = 0; i < GAME_OVER_OPTIONS; ++i)
	{
		gotoXY(gameOverOptionsPrintSpot, 17 + i);
		cout << gameOverOptions[i];
	}

	gotoXY(60, 17 + GAME_OVER_OPTIONS);
	
	while(game == E_GAME_OVER)
	{
		switch(getch())
		{
		case'1':
			game = E_MAIN_MENU;
			break;
		case'2':
			game = E_QUIT_MENU;
			break;
		default:
			game = E_GAME_OVER;
			break;
		}
	}

}

void gameLoop(string maps[], const size_t NUM_OF_MAPS, GAMESTATE &game, Loadables &loads)
{
	for(size_t currentLevel = loads.level; currentLevel < NUM_OF_MAPS; ++currentLevel)
	{
		if(game == E_GAME)
		{
			levelLoop(maps[currentLevel], game, currentLevel, loads);
		}
		else
		{
			break;
		}

		//Gives player a life after each level
		loads.playerLives += g_LIVES_PER_WIN;
	}
	game = E_MAIN_MENU;
}

//Pause Menu stuff
void saveMenu(Loadables loads)
{
	int numOfSaves = findSaveFiles();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cls();
	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t SAVE_MENU_TITLE = 8;
	string saveMenuTitle[SAVE_MENU_TITLE] = 
	{
		":'######:::::'###::::'##::::'##:'########:",
		"'##... ##:::'## ##::: ##:::: ##: ##.....::",
		" ##:::..:::'##:. ##:: ##:::: ##: ##:::::::",
		". ######::'##:::. ##: ##:::: ##: ######:::",
		":..... ##: #########:. ##:: ##:: ##...::::",
		"'##::: ##: ##.... ##::. ## ##::: ##:::::::",
		". ######:: ##:::: ##:::. ###:::: ########:",
		":......:::..:::::..:::::...:::::........::"
	};

	int saveMenuTitlePrintSpot = consoleSize.X/2 - saveMenuTitle[0].length()/2;

	for(size_t i = 0; i < SAVE_MENU_TITLE; ++i)
	{
		gotoXY(saveMenuTitlePrintSpot, 6 + i);
		cout << saveMenuTitle[i];
	}

	if(numOfSaves < 5)
	{
		string qnSaveName = "(Max. 20 Chars.)  ";
		string saveFileName;

		gotoXY(consoleSize.X/2 - qnSaveName.length(), 18 + SAVE_MENU_TITLE);
		cout << qnSaveName;
		qnSaveName = "Enter a Save name: ";
		gotoXY(consoleSize.X/2 - qnSaveName.length(), 17 + SAVE_MENU_TITLE);
		cout << qnSaveName;
		cin >> saveFileName;
		flushInputBuffer();

		while(saveFileName.length() > 20)
		{
			cls();
			printBorder();

			colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			for(size_t i = 0; i < SAVE_MENU_TITLE; ++i)
			{
				gotoXY(saveMenuTitlePrintSpot, 6 + i);
				cout << saveMenuTitle[i];
			}

			qnSaveName = "Save name has exceeded 20 characters!";
			gotoXY(qnSaveName.length()/2, 17 + SAVE_MENU_TITLE);
			cout << qnSaveName;
			qnSaveName = "Enter another Save name: ";
			gotoXY(consoleSize.X/2 - qnSaveName.length(), 18 + SAVE_MENU_TITLE);
			cout << qnSaveName;
			cin >> saveFileName;
			flushInputBuffer();
		}

		gotoXY(consoleSize.X/2, 17 + SAVE_MENU_TITLE);

		saveGame(loads, saveFileName);
	}
	else
	{
		string qnDelete = "Save file limit reached.";
		gotoXY(consoleSize.X/2 - qnDelete.length()/2, 14 + SAVE_MENU_TITLE);
		cout << qnDelete;

		qnDelete = "Do you want to delete a save file?";
		gotoXY(consoleSize.X/2 - qnDelete.length()/2, 15 + SAVE_MENU_TITLE);
		cout << qnDelete;

		const size_t CANT_SAVE_OPTIONS = 8;
		string cantSaveOptions[CANT_SAVE_OPTIONS] =
		{
			" __________________ ",
			"|                  |", //Total Length 20
			"|                  |",
			"|     (1) Yes      |",
			"|                  |",
			"|     (2) No       |",
			"|                  |",
			"|__________________|"
		};

		int cantSaveOptionsPrintSpot = consoleSize.X/2 - cantSaveOptions[0].length()/2;

		for(size_t i = 0; i < CANT_SAVE_OPTIONS; ++i)
		{
			gotoXY(cantSaveOptionsPrintSpot, 18 + SAVE_MENU_TITLE + i);
			cout << cantSaveOptions[i];
		}

		bool exit = false;
		while(!exit)
		{
			switch(getch())
			{
				case'1':
					if(deleteMenu())
					{
						saveMenu(loads);
					}
					exit = true;
					break;
				case'2':
					exit = true;
					break;
			}
		}
	}
}

void loadMenu(GAMESTATE &game, Loadables &loadInfo)
{
	vector<string> listOfLevels;
	findSaveFiles(listOfLevels);

	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t LOAD_MENU_TITLE = 8;
	string loadMenuTitle[LOAD_MENU_TITLE] = 
	{
		"'##::::::::'#######:::::'###::::'########::::::'######::::::'###::::'##::::'##:'########:",
		" ##:::::::'##.... ##:::'## ##::: ##.... ##::::'##... ##::::'## ##::: ###::'###: ##.....::",
		" ##::::::: ##:::: ##::'##:. ##:: ##:::: ##:::: ##:::..::::'##:. ##:: ####'####: ##:::::::",
		" ##::::::: ##:::: ##:'##:::. ##: ##:::: ##:::: ##::'####:'##:::. ##: ## ### ##: ######:::",
		" ##::::::: ##:::: ##: #########: ##:::: ##:::: ##::: ##:: #########: ##. #: ##: ##...::::",
		" ##::::::: ##:::: ##: ##.... ##: ##:::: ##:::: ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::",
		" ########:. #######:: ##:::: ##: ########:::::. ######::: ##:::: ##: ##:::: ##: ########:",
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

	while(game == E_LOAD_MENU)
	{
		char input = getch();

		if (input == '1')
		{
			game = E_MAIN_MENU;
		}
		else if (numOfSaves > 0)
		{
			if (input > '1' && input <= '9')
			{
				if(loadGame(loadInfo, listOfLevels[input - 48 - 2]))
				{
					game = E_GAME;
				}
				else
				{
					string errorLoading = "Error loading game!";
					gotoXY(consoleSize.X/2 - errorLoading.length()/2, 17 + LOAD_MENU_OPTIONS_HEAD + saveFilesToPrint + LOAD_MENU_OPTIONS_FOOT);
					cout << errorLoading;
				}
			}
		}
		else
		{
			game = E_LOAD_MENU;
		}

	}
}

bool pauseMenu(E_LEVEL_STATE &levelState, Loadables loads)
{
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cls();

	printBorder();
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t PAUSE_SCREEN_TITLE = 8;
	string pausescreen[PAUSE_SCREEN_TITLE] =
	{
		"'########:::::'###::::'##::::'##::'######::'########:'########::",
		" ##.... ##:::'## ##::: ##:::: ##:'##... ##: ##.....:: ##.... ##:",
		" ##:::: ##::'##:. ##:: ##:::: ##: ##:::..:: ##::::::: ##:::: ##:",
		" ########::'##:::. ##: ##:::: ##:. ######:: ######::: ##:::: ##:",
		" ##.....::: #########: ##:::: ##::..... ##: ##...:::: ##:::: ##:",
		" ##:::::::: ##.... ##: ##:::: ##:'##::: ##: ##::::::: ##:::: ##:",
		" ##:::::::: ##:::: ##:. #######::. ######:: ########: ########::",
		"..:::::::::..:::::..:::.......::::......:::........::........:::"
	};
	int pausescreenPrintSpot = consoleSize.X/2 - pausescreen[0].length()/2;

	for(size_t i = 0; i < PAUSE_SCREEN_TITLE; ++i)
	{
		gotoXY(pausescreenPrintSpot, 6 + i);
		cout << pausescreen[i];
	}

	const size_t PAUSE_MENU_OPTIONS = 8;
	string pauseMenuOptions[PAUSE_MENU_OPTIONS] =
	{
		" ___________________ ",
		"|                   |",
		"|                   |",
		"|  (1) Resume Game  |",
		"|  (2) Save Game    |",
		"|  (3) Exit Level   |",
		"|                   |",
		"|___________________|"
	};

	int pauseMenuOptionsPrintSpot = consoleSize.X/2 - pauseMenuOptions[0].length()/2;

	for(size_t i = 0; i < PAUSE_MENU_OPTIONS; ++i)
	{
		gotoXY(pauseMenuOptionsPrintSpot, 17 + i);
		cout << pauseMenuOptions[i];
	}

	gotoXY(consoleSize.X/2, 17 + PAUSE_MENU_OPTIONS);
	
	while (levelState == E_PAUSE)
	{
		switch(getch())
		{
			case'1':
				levelState = E_PLAYING;
				return false;
				break;
			case'2':
				saveMenu(loads);
				levelState = E_PLAYING;
				return false;
				break;
			case'3':
				levelState = E_LOSS;
				return true;
				break;
			default:
				levelState = E_PAUSE;
				break;
		}
	}
}
void loadingScreen(string mapName)
{
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	cls();
	const size_t LOADING_SCREEN_TITLE = 8;
	string loadingscreen[LOADING_SCREEN_TITLE] =
	{
		"'##::::::::'#######:::::'###::::'########::'####:'##::: ##::'######:::",
		" ##:::::::'##.... ##:::'## ##::: ##.... ##:. ##:: ###:: ##:'##... ##::",
		" ##::::::: ##:::: ##::'##:. ##:: ##:::: ##:: ##:: ####: ##: ##:::..:::",
		" ##::::::: ##:::: ##:'##:::. ##: ##:::: ##:: ##:: ## ## ##: ##::'####:",
		" ##::::::: ##:::: ##: #########: ##:::: ##:: ##:: ##. ####: ##::: ##::",
		" ##::::::: ##:::: ##: ##.... ##: ##:::: ##:: ##:: ##:. ###: ##::: ##::",
		" ########:. #######:: ##:::: ##: ########::'####: ##::. ##:. ######:::",
		"........:::.......:::..:::::..::........:::....::..::::..:::......::::"
	};
	int loadingscreenPrintSpot = defaultConsoleSize.X/2 - loadingscreen[0].length()/2;

	for(size_t i = 0; i < LOADING_SCREEN_TITLE; ++i)
	{
		gotoXY(loadingscreenPrintSpot, 6 + i);
		cout << loadingscreen[i];
	}

	string mapLoading = "Map :" + mapName;

	gotoXY(defaultConsoleSize.X/2 - mapLoading.length()/2, 10 + LOADING_SCREEN_TITLE);

	cout << mapLoading;
}

void startScreen(string mapName)
{
	cls();
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	const size_t START_SCREEN_TITLE = 8;
	string startscreen[START_SCREEN_TITLE] =
	{
		"'##::: ##:'########:'##::::'##:'########:::::::'##:::::::'########:'##::::'##:'########:'##:::::::",
		" ###:: ##: ##.....::. ##::'##::... ##..:::::::: ##::::::: ##.....:: ##:::: ##: ##.....:: ##:::::::",
		" ####: ##: ##::::::::. ##'##:::::: ##:::::::::: ##::::::: ##::::::: ##:::: ##: ##::::::: ##:::::::",
		" ## ## ##: ######:::::. ###::::::: ##:::::::::: ##::::::: ######::: ##:::: ##: ######::: ##:::::::",
		" ##. ####: ##...:::::: ## ##:::::: ##:::::::::: ##::::::: ##...::::. ##:: ##:: ##...:::: ##:::::::",
		" ##:. ###: ##:::::::: ##:. ##::::: ##:::::::::: ##::::::: ##::::::::. ## ##::: ##::::::: ##:::::::",
		" ##::. ##: ########: ##:::. ##:::: ##:::::::::: ########: ########:::. ###:::: ########: ########:",
		"..::::..::........::..:::::..:::::..:::::::::::........::........:::::...:::::........::........::"
	};
	int startscreenPrintSpot = defaultConsoleSize.X/2 - startscreen[0].length()/2;

	for(size_t i = 0; i < START_SCREEN_TITLE; ++i)
	{
		gotoXY(startscreenPrintSpot, 6 + i);
		cout << startscreen[i];
	}

	string mapLoaded = "Map :" + mapName;

	gotoXY(defaultConsoleSize.X/2 - mapLoaded.length()/2, 10 + START_SCREEN_TITLE);

	cout << mapLoaded;
}

void endScreen()
{
	newSetConsoleSize(defaultConsoleSize);
	cls();
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	const size_t END_SCREEN_TITLE = 8;
	string endscreen[END_SCREEN_TITLE] =
	{
		":'######::::::'###::::'##::::'##:'########::::::::'#######::'##::::'##:'########:'########::",
		"'##... ##::::'## ##::: ###::'###: ##.....::::::::'##.... ##: ##:::: ##: ##.....:: ##.... ##:",
		" ##:::..::::'##:. ##:: ####'####: ##::::::::::::: ##:::: ##: ##:::: ##: ##::::::: ##:::: ##:",
		" ##::'####:'##:::. ##: ## ### ##: ######::::::::: ##:::: ##: ##:::: ##: ######::: ########::",
		" ##::: ##:: #########: ##. #: ##: ##...:::::::::: ##:::: ##:. ##:: ##:: ##...:::: ##.. ##:::",
		" ##::: ##:: ##.... ##: ##:.:: ##: ##::::::::::::: ##:::: ##::. ## ##::: ##::::::: ##::. ##::",
		". ######::: ##:::: ##: ##:::: ##: ########:::::::. #######::::. ###:::: ########: ##:::. ##:",
		":......::::..:::::..::..:::::..::........:::::::::.......::::::...:::::........::..:::::..::"
	};
	int endscreenPrintSpot = defaultConsoleSize.X/2 - endscreen[0].length()/2;

	for(size_t i = 0; i < END_SCREEN_TITLE; ++i)
	{
		gotoXY(endscreenPrintSpot, 6 + i);
		cout << endscreen[i];
	}
	cout << endl << endl << endl <<"                    Press Enter to conitnue ";
	getch();
}
void winScreen()
{
	newSetConsoleSize(defaultConsoleSize);
	cls();
	system("color 0F");
	const size_t END_SCREEN_TITLE = 8;
	string endscreen[END_SCREEN_TITLE] =
	{
		"'##::::'##:'####::'######::'########::'#######::'########::'##:::'##:",
		" ##:::: ##:. ##::'##... ##:... ##..::'##.... ##: ##.... ##:. ##:'##::",
		" ##:::: ##:: ##:: ##:::..::::: ##:::: ##:::: ##: ##:::: ##::. ####:::",
		" ##:::: ##:: ##:: ##:::::::::: ##:::: ##:::: ##: ########::::. ##::::",
		". ##:: ##::: ##:: ##:::::::::: ##:::: ##:::: ##: ##.. ##:::::: ##::::",
		":. ## ##:::: ##:: ##::: ##:::: ##:::: ##:::: ##: ##::. ##::::: ##::::",
		"::. ###::::'####:. ######::::: ##::::. #######:: ##:::. ##:::: ##::::",
		":::...:::::....:::......::::::..::::::.......:::..:::::..:::::..:::::"
	};
	int endscreenPrintSpot = defaultConsoleSize.X/2 - endscreen[0].length()/2;

	for(size_t i = 0; i < END_SCREEN_TITLE; ++i)
	{
		gotoXY(endscreenPrintSpot, 6 + i);
		cout << endscreen[i];
	}
	const size_t PAUSE_MENU_OPTIONS = 6;
	string pauseMenuOptions[PAUSE_MENU_OPTIONS] =
	{
		" You have completed PacGun, Congratulations ",
		" This game is brought to you by Team 11     ",
		"       Members :   Tng Kah Wei              ",
		"                   Leng Wei Shao, Sean      ",
		"                   Rayner Tay Yi Zhe        ",
		"                   Koh Tim Lin              "
	};

	int pauseMenuOptionsPrintSpot = consoleSize.X/2 - pauseMenuOptions[0].length()/2;

	for(size_t i = 0; i < PAUSE_MENU_OPTIONS; ++i)
	{
		gotoXY(pauseMenuOptionsPrintSpot, 17 + i);
		cout << pauseMenuOptions[i];
	}

	gotoXY(60, 17 + PAUSE_MENU_OPTIONS);

	pressToContinue(20 + PAUSE_MENU_OPTIONS);
}

bool quit(GAMESTATE &game)
{
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cls();

	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	
	const size_t QUIT_SCREEN_TITLE = 8;
	string quitScreen[QUIT_SCREEN_TITLE] =
	{
		":'#######::'##::::'##:'####:'########::'#######::",
		"'##.... ##: ##:::: ##:. ##::... ##..::'##.... ##:",
		" ##:::: ##: ##:::: ##:: ##::::: ##::::..:::: ##::",
		" ##:::: ##: ##:::: ##:: ##::::: ##:::::::: ###:::",
	 	" ##:'## ##: ##:::: ##:: ##::::: ##::::::: ##.::::",
		" ##:.. ##:: ##:::: ##:: ##::::: ##:::::::..::::::",
		": ##### ##:. #######::'####:::: ##:::::::'##:::::",
		":.....:..:::.......:::....:::::..::::::::..::::::"
	};
	int quitScreenPrintSpot = defaultConsoleSize.X/2 - quitScreen[0].length()/2;

	for(size_t i = 0; i < QUIT_SCREEN_TITLE; ++i)
	{
		gotoXY(quitScreenPrintSpot, 6 + i);
		cout << quitScreen[i];
	}

	const size_t QUIT_MENU_OPTIONS = 8;
	string quitMenuOptions[QUIT_MENU_OPTIONS] =
	{
		" ___________________ ",
		"|                   |",
		"|                   |",
		"|   (1) Return      |",
		"|                   |",
		"|   (2) Exit Game   |",
		"|                   |",
		"|___________________|"
	};

	int quitMenuOptionsPrintSpot = consoleSize.X/2 - quitMenuOptions[0].length()/2;

	for(size_t i = 0; i < QUIT_MENU_OPTIONS; ++i)
	{
		gotoXY(quitMenuOptionsPrintSpot, 17 + i);
		cout << quitMenuOptions[i];
	}

	gotoXY(consoleSize.X/2, 17 + QUIT_MENU_OPTIONS);

	while(game == E_QUIT_MENU)
	{
		switch(getch())
		{
		case '1':
			game = E_MAIN_MENU;
			return false;
			break;
		case '2':
			game = E_EXIT;
			return true;
			break;
		default:
			game = E_QUIT_MENU;
			break;
		}
	}

	return false;
}

void deleteMenu(GAMESTATE &game)
{
	while(game == E_DELETE_SAVES)
	{
		vector<string> listOfLevels;
		findSaveFiles(listOfLevels);

		colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		cls();

		printBorder();
		colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

		const size_t DELETE_MENU_TITLE = 8;
		string deleteMenuTitle[DELETE_MENU_TITLE] = 
		{
			"'########::'########:'##:::::::'########:'########:'########:",
			" ##.... ##: ##.....:: ##::::::: ##.....::... ##..:: ##.....::",
			" ##:::: ##: ##::::::: ##::::::: ##:::::::::: ##:::: ##:::::::",
			" ##:::: ##: ######::: ##::::::: ######:::::: ##:::: ######:::",
			" ##:::: ##: ##...:::: ##::::::: ##...::::::: ##:::: ##...::::",
			" ##:::: ##: ##::::::: ##::::::: ##:::::::::: ##:::: ##:::::::",
			" ########:: ########: ########: ########:::: ##:::: ########:",
			"........:::........::........::........:::::..:::::........::"
		};

		int deleteMenuTitlePrintSpot = consoleSize.X/2 - deleteMenuTitle[0].length()/2;

		for(size_t i = 0; i < DELETE_MENU_TITLE; ++i)
		{
			gotoXY(deleteMenuTitlePrintSpot, 6 + i);
			cout << deleteMenuTitle[i];
		}

		const size_t DELETE_MENU_OPTIONS_HEAD = 5;
		string deleteMenuOptionsHead[DELETE_MENU_OPTIONS_HEAD] =
		{
			" _______________________________ ",
			"|                               |", //Total Length 20
			"|                               |",
			"|  (1) Return                   |",
			"|                               |"
		};

		const size_t DELETE_MENU_OPTIONS_FOOT = 2;
		string deleteMenuOptionsFoot[DELETE_MENU_OPTIONS_FOOT] =
		{
			"|                               |",
			"|_______________________________|"
		};

		int deleteMenuOptionsPrintSpot = consoleSize.X/2 - deleteMenuOptionsHead[0].length()/2;
		int deleteMenuOptionsHeadLength = deleteMenuOptionsHead[0].length();

		for(size_t i = 0; i < DELETE_MENU_OPTIONS_HEAD; ++i)
		{
			gotoXY(deleteMenuOptionsPrintSpot, 17 + i);
			cout << deleteMenuOptionsHead[i];
		}

		size_t numOfSaves = 0;
		bool saveFilesPresent = false;
		for(; numOfSaves < listOfLevels.size(); ++numOfSaves)
		{
			gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves);
			cout << "|  (" << numOfSaves + 2 << ") " << listOfLevels[numOfSaves];
			gotoXY(deleteMenuOptionsPrintSpot + deleteMenuOptionsHead[0].length() - 1, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves);
			cout << "|";

			saveFilesPresent = true;
		}

		int saveFilesToPrint = numOfSaves;

		if(!saveFilesPresent)
		{
			gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves);
			cout << "|                               |";
			gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves + 1);
			cout << "|        No Saves Found         |";
			saveFilesToPrint = 2;
		}

		for(size_t i = 0; i < DELETE_MENU_OPTIONS_FOOT; ++i)
		{
			gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + i);
			cout << deleteMenuOptionsFoot[i];
		}

		gotoXY(consoleSize.X/2, 17 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);

		while(game == E_DELETE_SAVES)
		{
			char input = getch();

			if (input == '1')
			{
				game = E_MAIN_MENU;
			}
			else if (numOfSaves > 0)
			{
				if (input > '1' && input <= '9')
				{
					if(deleteGame(listOfLevels[input - 48 - 2]))
					{
						string deletePassMsg = "Successfully deleted save!";
						gotoXY(consoleSize.X/2 - deletePassMsg.length()/2, 24 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);
						cout << deletePassMsg;
						gotoXY(consoleSize.X/2 - deletePassMsg.length()/2, 25 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);
						system("pause");
						game = E_DELETE_SAVES;
						break;
					}
					else
					{
						string errorLoading = "Error deleting save!";
						gotoXY(consoleSize.X/2 - errorLoading.length()/2, 24 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);
						cout << errorLoading;
					}
				}
			}
			else
			{
				game = E_DELETE_SAVES;
			}
		}
	}
}

bool deleteMenu()
{
	bool returnValue = false;
	vector<string> listOfLevels;
	findSaveFiles(listOfLevels);

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cls();

	printBorder();

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t DELETE_MENU_TITLE = 8;
	string deleteMenuTitle[DELETE_MENU_TITLE] = 
	{
		"'########::'########:'##:::::::'########:'########:'########:",
		" ##.... ##: ##.....:: ##::::::: ##.....::... ##..:: ##.....::",
		" ##:::: ##: ##::::::: ##::::::: ##:::::::::: ##:::: ##:::::::",
		" ##:::: ##: ######::: ##::::::: ######:::::: ##:::: ######:::",
		" ##:::: ##: ##...:::: ##::::::: ##...::::::: ##:::: ##...::::",
		" ##:::: ##: ##::::::: ##::::::: ##:::::::::: ##:::: ##:::::::",
		" ########:: ########: ########: ########:::: ##:::: ########:",
		"........:::........::........::........:::::..:::::........::"
	};

	int deleteMenuTitlePrintSpot = consoleSize.X/2 - deleteMenuTitle[0].length()/2;

	for(size_t i = 0; i < DELETE_MENU_TITLE; ++i)
	{
		gotoXY(deleteMenuTitlePrintSpot, 6 + i);
		cout << deleteMenuTitle[i];
	}

	const size_t DELETE_MENU_OPTIONS_HEAD = 5;
	string deleteMenuOptionsHead[DELETE_MENU_OPTIONS_HEAD] =
	{
		" _______________________________ ",
		"|                               |", //Total Length 20
		"|                               |",
		"|  (1) Return                   |",
		"|                               |"
	};

	const size_t DELETE_MENU_OPTIONS_FOOT = 2;
	string deleteMenuOptionsFoot[DELETE_MENU_OPTIONS_FOOT] =
	{
		"|                               |",
		"|_______________________________|"
	};

	int deleteMenuOptionsPrintSpot = consoleSize.X/2 - deleteMenuOptionsHead[0].length()/2;
	int deleteMenuOptionsHeadLength = deleteMenuOptionsHead[0].length();

	for(size_t i = 0; i < DELETE_MENU_OPTIONS_HEAD; ++i)
	{
		gotoXY(deleteMenuOptionsPrintSpot, 17 + i);
		cout << deleteMenuOptionsHead[i];
	}

	size_t numOfSaves = 0;
	bool saveFilesPresent = false;
	for(; numOfSaves < listOfLevels.size(); ++numOfSaves)
	{
		gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves);
		cout << "|  (" << numOfSaves + 2 << ") " << listOfLevels[numOfSaves];
		gotoXY(deleteMenuOptionsPrintSpot + deleteMenuOptionsHead[0].length() - 1, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves);
		cout << "|";

		saveFilesPresent = true;
	}

	int saveFilesToPrint = numOfSaves;

	if(!saveFilesPresent)
	{
		gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves);
		cout << "|                               |";
		gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + numOfSaves + 1);
		cout << "|        No Saves Found         |";
		saveFilesToPrint = 2;
	}

	for(size_t i = 0; i < DELETE_MENU_OPTIONS_FOOT; ++i)
	{
		gotoXY(deleteMenuOptionsPrintSpot, 17 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + i);
		cout << deleteMenuOptionsFoot[i];
	}

	gotoXY(consoleSize.X/2, 17 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);

	while(true)
	{
		char input = getch();

		if (input == '1')
		{
			break;
		}
		else if (numOfSaves > 0)
		{
			if (input > '1' && input <= '9')
			{
				if(deleteGame(listOfLevels[input - 48 - 2]))
				{
					string deletePassMsg = "Successfully deleted save!";
					gotoXY(consoleSize.X/2 - deletePassMsg.length()/2, 19 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);
					cout << deletePassMsg;
					gotoXY(consoleSize.X/2 - deletePassMsg.length()/2, 20 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);
					returnValue = true;
					break;
				}
				else
				{
					string errorLoading = "Error deleting save!";
					gotoXY(consoleSize.X/2 - errorLoading.length()/2, 19 + DELETE_MENU_OPTIONS_HEAD + saveFilesToPrint + DELETE_MENU_OPTIONS_FOOT);
					cout << errorLoading;
				}
			}
		}
	}

	return returnValue;
}

void victoryScreen()
{
	const int VICTORY_SCREEN_SIZE = 13;
	string victoryScreen[VICTORY_SCREEN_SIZE] =
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
	for(int a = 0; a < VICTORY_SCREEN_SIZE; ++a)
	{
		gotoXY(consoleSize.X/2 - victoryScreen[a].length()/2, 10 + a);
		cout << victoryScreen[a];
	}
	
	pressToContinue(17 + VICTORY_SCREEN_SIZE);
}

void loseScreen()
{
	const int LOSE_SCREEN_SIZE = 13;
	string loseScreen[LOSE_SCREEN_SIZE] =
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
	for(int a = 0; a < LOSE_SCREEN_SIZE; ++a)
	{
		gotoXY(consoleSize.X/2 - loseScreen[a].length()/2, 10 + a);
		cout << loseScreen[a];
	}

	pressToContinue(17 + LOSE_SCREEN_SIZE);
}

void loadCustomGame(GAMESTATE &game)
{

}