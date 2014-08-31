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
#include "customLevels.h"


extern COORD consoleSize;
extern COORD defaultConsoleSize;

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;

void mainMenu(GAMESTATE &game)
{
	extern bool keyPressed[E_MAX_KEYS];
	int selection = 0;
	int oldSelection = 0;
	bool selectionChanged = false;

	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_BLUE);
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

	const size_t MAIN_MENU_OPTIONS = 13;
	string mainMenuOptions[MAIN_MENU_OPTIONS] =
	{
		" _____________________",
		"|                     |", //Total Length 20
		"|                     |",
		"|      Start Game     |",
		"|      Load Saves     |",
		"|      Play Custom    |",
		"|      Game Guide     |",
		"|      Del Saves      |",
		"|      High Scores    |",
		"|      About          |",
		"|      Exit Game      |",
		"|                     |",
		"|_____________________|"
	};

	int mainMenuOptionsPrintSpot = defaultConsoleSize.X/2 - mainMenuOptions[0].length()/2;

	for(size_t i = 0; i < MAIN_MENU_OPTIONS; ++i)
	{
		gotoXY(mainMenuOptionsPrintSpot, 17 + i);
		cout << mainMenuOptions[i];
	}

	//New Menu System
	gotoXY(consoleSize.X/2 - mainMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
	cout << g_MENU_TICKER;

	while(game == E_MAIN_MENU)
	{
		gotoXY(consoleSize.X/2, 17 + 4 + MAIN_MENU_OPTIONS);
		selectionChanged = false;
		getInput();

		if(keyPressed[E_UP_KEY] && selection > 0)
		{
			oldSelection = selection;
			--selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection < 7)
		{
			oldSelection = selection;
			++selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			switch(selection)
			{
				case 0:
					game = E_GAME;
					break;
				case 1:
					game = E_LOAD_SAVES;
					break;
				case 2:
					game = E_LOAD_CUSTOM;
					break;
				case 3:
					game = E_GAME_GUIDE;
					break;
				case 4:
					game = E_DELETE_SAVES;
					break;
				case 5:
					game = E_HIGH_SCORES;
					break;
				case 6:
					game = E_ABOUT_SCREEN;
					break;
				case 7:
					game = E_QUIT_MENU;
					break;
				default:
					game = E_MAIN_MENU;
					break;
			}
		}

		if(selectionChanged)
		{
			gotoXY(consoleSize.X/2 - mainMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + oldSelection);
			cout << " ";
			gotoXY(consoleSize.X/2 - mainMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
			cout << g_MENU_TICKER;
		}
		Sleep(100);
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
	extern bool keyPressed[E_MAX_KEYS];

	int selection = -1;
	int oldSelection = -1;
	bool selectionChanged = false;

	vector<string> listOfLevels;
	findSaveFiles(listOfLevels);
	
	int maxSaveNameLength = 6; //Length of "Return"

	//Get longest save name
	for(size_t i = 0; i < listOfLevels.size(); ++i)
	{
		if(listOfLevels[i].length() >  maxSaveNameLength)
		{
			 maxSaveNameLength = listOfLevels[i].length();
		}
	}

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

	string loadMenuOptionsHead = "Return";

	int loadMenuOptionsPrintSpot = consoleSize.X/2 - maxSaveNameLength/2;
	int loadMenuOptionsHeadLength = loadMenuOptionsHead.length();

	gotoXY(loadMenuOptionsPrintSpot, 21);
	cout << loadMenuOptionsHead;

	size_t numOfSaves = 0;
	bool saveFilesPresent = false;
	for(; numOfSaves < listOfLevels.size(); ++numOfSaves)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23 + numOfSaves);
		cout << listOfLevels[numOfSaves];

		saveFilesPresent = true;
	}

	int saveFilesToPrint = numOfSaves;

	if(!saveFilesPresent)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23);
		cout << "No Saves";
		saveFilesToPrint = 2;
	}

	//Draws Border
	//--Top
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19);
	for(int i = 1; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Bottom
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + saveFilesToPrint);
	for(int i = 1; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Left
	for(int i = 1; i < saveFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length() - 2, 19 + i);
		cout << "|";
	}
	//--Right
	for(int i = 1; i < saveFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 + maxSaveNameLength/2 + g_MENU_TICKER.length() + 2, 19 + i);
		cout << "|";
	}
	
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
	cout << g_MENU_TICKER;

	while(game == E_LOAD_SAVES)
	{
		gotoXY(consoleSize.X/2, 26 + numOfSaves);
		selectionChanged = false;
		getInput();

		if(keyPressed[E_UP_KEY] && selection > -1)
		{
			oldSelection = selection;
			--selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection + 1< numOfSaves)
		{
			oldSelection = selection;
			++selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			if (selection == -1)
			{
				game = E_MAIN_MENU;
			}
			else if (numOfSaves > 0)
			{
				if(loadGame(loadInfo, listOfLevels[selection]))
				{
					game = E_GAME;
				}
				else
				{
					string errorLoading = "Error loading game!";
					gotoXY(consoleSize.X/2 - errorLoading.length()/2, 20 + saveFilesToPrint + 3);
					cout << errorLoading;
				}
			}
			else
			{
				game = E_LOAD_SAVES;
			}
		}

		if(selectionChanged)
		{
			if (oldSelection == -1)
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
				cout << " ";
			}
			else
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 23 + oldSelection);
				cout << " ";
			}

			if (selection == -1)
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
				cout << g_MENU_TICKER;
			}
			else
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 23 + selection);
				cout << g_MENU_TICKER;
			}
		}
		Sleep(100);
	}
}

bool pauseMenu(E_LEVEL_STATE &levelState, Loadables loads, bool isCustom)
{
	extern bool keyPressed[E_MAX_KEYS];
	int selection = 0;
	int oldSelection = 0;
	bool selectionChanged = false;
	int maxSelection = 2;

	if(isCustom)
	{
		maxSelection = 1;
	}

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
		" ____________________",
		"|                    |",
		"|                    |",
		"|      Resume Game   |",
		"|      Save Game     |",
		"|      Exit Level    |",
		"|                    |",
		"|____________________|"
	};

	if(isCustom)
	{
		pauseMenuOptions[4] = "|                    |";
	}

	int pauseMenuOptionsPrintSpot = consoleSize.X/2 - pauseMenuOptions[0].length()/2;

	for(size_t i = 0; i < PAUSE_MENU_OPTIONS; ++i)
	{
		gotoXY(pauseMenuOptionsPrintSpot, 17 + i);
		cout << pauseMenuOptions[i];
	}

	//New Menu System
	gotoXY(consoleSize.X/2 - pauseMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
	cout << g_MENU_TICKER;

	while(levelState == E_PAUSE)
	{
		gotoXY(consoleSize.X/2, 17 + 4 + PAUSE_MENU_OPTIONS);
		selectionChanged = false;
		getInput();

		if(keyPressed[E_UP_KEY] && selection > 0)
		{
			oldSelection = selection;
			--selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection < maxSelection)
		{
			oldSelection = selection;
			++selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			switch(selection)
			{
				case 0:
					levelState = E_PLAYING;
					return false;
					break;
				case 1:
					if(isCustom)
					{
						levelState = E_LOSS;
						return true;
					}
					else
					{
						saveMenu(loads);
						levelState = E_PLAYING;
						return false;
					}
					break;
				case 2:
					if(!isCustom)
					{
						levelState = E_LOSS;
						return true;
					}
					break;
				default:
					levelState = E_PAUSE;
					break;
			}
		}

		if(selectionChanged)
		{
			if(isCustom)
			{
				gotoXY(consoleSize.X/2 - pauseMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + oldSelection * 2);
				cout << " ";
				gotoXY(consoleSize.X/2 - pauseMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection * 2);
				cout << g_MENU_TICKER;
			}
			else
			{
				gotoXY(consoleSize.X/2 - pauseMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + oldSelection);
				cout << " ";
				gotoXY(consoleSize.X/2 - pauseMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
				cout << g_MENU_TICKER;
			}
		}
		Sleep(100);
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
	
	pressToContinue(7 + END_SCREEN_TITLE);
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
	extern bool keyPressed[E_MAX_KEYS];
	int selection = 0;
	int oldSelection = 0;
	bool selectionChanged = false;

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
		"|      Return       |",
		"|                   |",
		"|      Exit Game    |",
		"|                   |",
		"|___________________|"
	};

	int quitMenuOptionsPrintSpot = consoleSize.X/2 - quitMenuOptions[0].length()/2;

	for(size_t i = 0; i < QUIT_MENU_OPTIONS; ++i)
	{
		gotoXY(quitMenuOptionsPrintSpot, 17 + i);
		cout << quitMenuOptions[i];
	}

	gotoXY(consoleSize.X/2 - quitMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
	cout << g_MENU_TICKER;

	while(game == E_QUIT_MENU)
	{
		gotoXY(consoleSize.X/2, 17 + 4 + QUIT_MENU_OPTIONS);
		selectionChanged = false;
		getInput();

		if(keyPressed[E_UP_KEY] && selection > 0)
		{
			oldSelection = selection;
			--selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection < 1)
		{
			oldSelection = selection;
			++selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			switch(selection)
			{
				case 0:
					game = E_MAIN_MENU;
					return false;
					break;
				case 1:
					game = E_EXIT;
					return true;
					break;
				default:
					game = E_QUIT_MENU;
					break;
			}
		}

		if(selectionChanged)
		{
			gotoXY(consoleSize.X/2 - quitMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + oldSelection * 2);
			cout << " ";
			gotoXY(consoleSize.X/2 - quitMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection * 2);
			cout << g_MENU_TICKER;
		}
		Sleep(100);
	}

	return false;
}

void deleteMenu(GAMESTATE &game)
{
	extern bool keyPressed[E_MAX_KEYS];

	while(game == E_DELETE_SAVES)
	{
		int selection = -1;
		int oldSelection = -1;
		bool selectionChanged = false;

		vector<string> listOfLevels;
		findSaveFiles(listOfLevels);

		int maxSaveNameLength = 6; //Length of "return"
		
		//Get longest map name
		for(size_t i = 0; i < listOfLevels.size(); ++i)
		{
			if(listOfLevels[i].length() >  maxSaveNameLength)
			{
				maxSaveNameLength = listOfLevels[i].length();
			}
		}

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

		string loadMenuOptionsHead = "Return";

		int loadMenuOptionsPrintSpot = consoleSize.X/2 - maxSaveNameLength/2;
		int loadMenuOptionsHeadLength = loadMenuOptionsHead.length();

		gotoXY(loadMenuOptionsPrintSpot, 21);
		cout << loadMenuOptionsHead;

		size_t numOfSaves = 0;
		bool saveFilesPresent = false;
		for(; numOfSaves < listOfLevels.size(); ++numOfSaves)
		{
			gotoXY(loadMenuOptionsPrintSpot, 23 + numOfSaves);
			cout << listOfLevels[numOfSaves];

			saveFilesPresent = true;
		}

		int saveFilesToPrint = numOfSaves;

		if(!saveFilesPresent)
		{
			gotoXY(loadMenuOptionsPrintSpot, 23);
			cout << "No Saves";
			saveFilesToPrint = 2;
		}

		//Draws Border
		//--Top
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19);
		for(int i = 1; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
		{
			cout << "_";
		}
		//--Bottom
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + saveFilesToPrint);
		for(int i = 1; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
		{
			cout << "_";
		}
		//--Left
		for(int i = 1; i < saveFilesToPrint + 5; ++i)
		{
			gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length() - 2, 19 + i);
			cout << "|";
		}
		//--Right
		for(int i = 1; i < saveFilesToPrint + 5; ++i)
		{
			gotoXY(consoleSize.X/2 + maxSaveNameLength/2 + g_MENU_TICKER.length() + 2, 19 + i);
			cout << "|";
		}

		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
		cout << g_MENU_TICKER;

		while(game == E_DELETE_SAVES)
		{
			gotoXY(consoleSize.X/2, 26 + numOfSaves);
			selectionChanged = false;
			getInput();

			if(keyPressed[E_UP_KEY] && selection > -1)
			{
				oldSelection = selection;
				--selection;
				selectionChanged = true;
			}
			else if(keyPressed[E_DOWN_KEY] && selection + 1< numOfSaves)
			{
				oldSelection = selection;
				++selection;
				selectionChanged = true;
			}
			else if(keyPressed[E_SPACE_KEY])
			{
				if (selection == -1)
				{
					game = E_MAIN_MENU;
				}
				else if (numOfSaves > 0)
				{
					if(deleteGame(listOfLevels[selection]))
					{
						string deletePassMsg = "Successfully deleted save!";
						gotoXY(consoleSize.X/2 - deletePassMsg.length()/2, 28 + saveFilesToPrint);
						cout << deletePassMsg;
						pressToContinue(29 + saveFilesToPrint);
						game = E_DELETE_SAVES;
						break;
					}
					else
					{
						string errorLoading = "Error deleting save!";
						gotoXY(consoleSize.X/2 - errorLoading.length()/2, 28 + saveFilesToPrint);
						cout << errorLoading;
					}
				}
				else
				{
					game = E_LOAD_SAVES;
				}
			}

			if(selectionChanged)
			{
				if (oldSelection == -1)
				{
					gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
					cout << " ";
				}
				else
				{
					gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 23 + oldSelection);
					cout << " ";
				}

				if (selection == -1)
				{
					gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
					cout << g_MENU_TICKER;
				}
				else
				{
					gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 23 + selection);
					cout << g_MENU_TICKER;
				}
			}
			Sleep(100);
		}
	}
}

bool deleteMenu()
{
	bool returnValue = false;

	extern bool keyPressed[E_MAX_KEYS];
	int selection = -1;
	int oldSelection = -1;
	bool selectionChanged = false;

	vector<string> listOfLevels;
	findSaveFiles(listOfLevels);

	int maxSaveNameLength = 6; //Length of "return"

	//Get longest map name
	for(size_t i = 0; i < listOfLevels.size(); ++i)
	{
		if(listOfLevels[i].length() >  maxSaveNameLength)
		{
			maxSaveNameLength = listOfLevels[i].length();
		}
	}

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

	string loadMenuOptionsHead = "Return";

	int loadMenuOptionsPrintSpot = consoleSize.X/2 - maxSaveNameLength/2;
	int loadMenuOptionsHeadLength = loadMenuOptionsHead.length();

	gotoXY(loadMenuOptionsPrintSpot, 21);
	cout << loadMenuOptionsHead;

	size_t numOfSaves = 0;
	bool saveFilesPresent = false;
	for(; numOfSaves < listOfLevels.size(); ++numOfSaves)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23 + numOfSaves);
		cout << listOfLevels[numOfSaves];

		saveFilesPresent = true;
	}

	int saveFilesToPrint = numOfSaves;

	if(!saveFilesPresent)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23);
		cout << "No Saves";
		saveFilesToPrint = 2;
	}

	//Draws Border
	//--Top
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19);
	for(int i = 1; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Bottom
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + saveFilesToPrint);
	for(int i = 1; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Left
	for(int i = 1; i < saveFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length() - 2, 19 + i);
		cout << "|";
	}
	//--Right
	for(int i = 1; i < saveFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 + maxSaveNameLength/2 + g_MENU_TICKER.length() + 2, 19 + i);
		cout << "|";
	}

	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
	cout << g_MENU_TICKER;

	while(true)
	{
		gotoXY(consoleSize.X/2, 26 + numOfSaves);
		selectionChanged = false;
		getInput();

		if(keyPressed[E_UP_KEY] && selection > -1)
		{
			oldSelection = selection;
			--selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection + 1< numOfSaves)
		{
			oldSelection = selection;
			++selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			if (selection == -1)
			{
				break;
			}
			else if (numOfSaves > 0)
			{
				if(deleteGame(listOfLevels[selection]))
				{
					string deletePassMsg = "Successfully deleted save!";
					gotoXY(consoleSize.X/2 - deletePassMsg.length()/2, 28 + saveFilesToPrint);
					cout << deletePassMsg;
					pressToContinue(29 + saveFilesToPrint);
					returnValue = true;
					break;
				}
				else
				{
					string errorLoading = "Error deleting save!";
					gotoXY(consoleSize.X/2 - errorLoading.length()/2, 28 + saveFilesToPrint);
					cout << errorLoading;
				}
			}
		}

		if(selectionChanged)
		{
			if (oldSelection == -1)
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
				cout << " ";
			}
			else
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 23 + oldSelection);
				cout << " ";
			}

			if (selection == -1)
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 21);
				cout << g_MENU_TICKER;
			}
			else
			{
				gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length(), 23 + selection);
				cout << g_MENU_TICKER;
			}
		}
		Sleep(100);
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

void loadCustomLevelMenu(GAMESTATE &game)
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

	extern bool keyPressed[E_MAX_KEYS];

	int selection = -1;
	int oldSelection = -1;
	bool selectionChanged = false;
	vector<string> listOfCustomMaps;
	findCustomMaps(listOfCustomMaps);

	int maxMapNameLength = 6; //Length of "Return"

	//Get longest map name
	for(size_t i = 0; i < listOfCustomMaps.size(); ++i)
	{
		if(listOfCustomMaps[i].length() > maxMapNameLength)
		{
			maxMapNameLength = listOfCustomMaps[i].length();
		}
	}

	printBorder();
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const size_t CUSTOM_MAPS_MENU_TITLE = 8;
	string customMapsMenuTitle[CUSTOM_MAPS_MENU_TITLE] = 
	{
		":'######::'##::::'##::'######::'########::'#######::'##::::'##::::'##::::'##::::'###::::'########:::'######::",
		"'##... ##: ##:::: ##:'##... ##:... ##..::'##.... ##: ###::'###:::: ###::'###:::'## ##::: ##.... ##:'##... ##:",
		" ##:::..:: ##:::: ##: ##:::..::::: ##:::: ##:::: ##: ####'####:::: ####'####::'##:. ##:: ##:::: ##: ##:::..::",
		" ##::::::: ##:::: ##:. ######::::: ##:::: ##:::: ##: ## ### ##:::: ## ### ##:'##:::. ##: ########::. ######::",
		" ##::::::: ##:::: ##::..... ##:::: ##:::: ##:::: ##: ##. #: ##:::: ##. #: ##: #########: ##.....::::..... ##:",
		" ##::: ##: ##:::: ##:'##::: ##:::: ##:::: ##:::: ##: ##:.:: ##:::: ##:.:: ##: ##.... ##: ##::::::::'##::: ##:",
		". ######::. #######::. ######::::: ##::::. #######:: ##:::: ##:::: ##:::: ##: ##:::: ##: ##::::::::. ######::",
		":......::::.......::::......::::::..::::::.......:::..:::::..:::::..:::::..::..:::::..::..::::::::::......:::"
	};

	int customMapsMenuTitlePrintSpot = consoleSize.X/2 - customMapsMenuTitle[0].length()/2;

	for(size_t i = 0; i < CUSTOM_MAPS_MENU_TITLE; ++i)
	{
		gotoXY(customMapsMenuTitlePrintSpot, 6 + i);
		cout << customMapsMenuTitle[i];
	}

	string customMapsMenuOptionsHead = "Return";

	int customMapsMenuOptionsPrintSpot = consoleSize.X/2 - maxMapNameLength/2;
	int customMapsMenuOptionsHeadLength = customMapsMenuOptionsHead.length();

	gotoXY(customMapsMenuOptionsPrintSpot, 21);
	cout << customMapsMenuOptionsHead;

	size_t numOfMaps = 0;
	bool mapFilesPresent = false;
	for(; numOfMaps < listOfCustomMaps.size(); ++numOfMaps)
	{
		gotoXY(customMapsMenuOptionsPrintSpot, 23 + numOfMaps);
		cout << listOfCustomMaps[numOfMaps];

		mapFilesPresent = true;
	}

	int mapFilesToPrint = numOfMaps;

	if(!mapFilesPresent)
	{
		gotoXY(customMapsMenuOptionsPrintSpot, 20 + numOfMaps + 1);
		cout << "No Saves";
		mapFilesToPrint = 2;
	}

	//Draws Border
	//--Top
	gotoXY(consoleSize.X/2 - maxMapNameLength/2 - 1 - g_MENU_TICKER.length(), 19);
	for(int i = 1; i < maxMapNameLength + (g_MENU_TICKER.length() + 1) * 2; ++i)
	{
		cout << "_";
	}
	//--Bottom
	gotoXY(consoleSize.X/2 - maxMapNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + mapFilesToPrint);
	for(int i = 1; i < maxMapNameLength + (g_MENU_TICKER.length() + 1) * 2; ++i)
	{
		cout << "_";
	}
	//--Left
	for(int i = 1; i < mapFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 - maxMapNameLength/2 - g_MENU_TICKER.length() - 2, 19 + i);
		cout << "|";
	}
	//--Right
	for(int i = 1; i < mapFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 + maxMapNameLength/2 + g_MENU_TICKER.length(), 19 + i);
		cout << "|";
	}

	gotoXY(consoleSize.X/2 - maxMapNameLength/2 - g_MENU_TICKER.length(), 21);
	cout << g_MENU_TICKER;

	while(game == E_LOAD_CUSTOM)
	{
		gotoXY(consoleSize.X/2, 25 + numOfMaps);
		selectionChanged = false;
		getInput();

		if(keyPressed[E_UP_KEY] && selection > -1)
		{
			oldSelection = selection;
			--selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection + 1 < numOfMaps)
		{
			oldSelection = selection;
			++selection;
			selectionChanged = true;
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			if(selection == -1)
			{
				game = E_MAIN_MENU;
			}
			else
			{
				game = E_LOAD_CUSTOM;
				customGame(listOfCustomMaps[selection]);
				break;
			}
		}

		if(selectionChanged)
		{
			if (oldSelection == -1)
			{
				gotoXY(consoleSize.X/2 - maxMapNameLength/2 - g_MENU_TICKER.length(), 21);
				cout << " ";
			}
			else
			{
				gotoXY(consoleSize.X/2 - maxMapNameLength/2 - g_MENU_TICKER.length(), 23 + oldSelection);
				cout << " ";
			}

			if (selection == -1)
			{
				gotoXY(consoleSize.X/2 - maxMapNameLength/2 - g_MENU_TICKER.length(), 21);
				cout << g_MENU_TICKER;
			}
			else
			{
				gotoXY(consoleSize.X/2 - maxMapNameLength/2 - g_MENU_TICKER.length(), 23 + selection);
				cout << g_MENU_TICKER;
			}
		}
		Sleep(100);
	}
}

void aboutScreen()
{
	newSetConsoleSize(defaultConsoleSize);

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cls();
	
	const size_t ABOUT_SCREEN_TITLE = 8;
	string title[ABOUT_SCREEN_TITLE] =
	{
		"'########:::::'###:::::'######:::'######:::'##::::'##:'##::: ##:",
		" ##.... ##:::'## ##:::'##... ##:'##... ##:: ##:::: ##: ###:: ##:", 
		" ##:::: ##::'##:. ##:: ##:::..:: ##:::..::: ##:::: ##: ####: ##:",
		" ########::'##:::. ##: ##::::::: ##::'####: ##:::: ##: ## ## ##:",
		" ##.....::: #########: ##::::::: ##::: ##:: ##:::: ##: ##. ####:",
		" ##:::::::: ##.... ##: ##::: ##: ##::: ##:: ##:::: ##: ##:. ###:",
		" ##:::::::: ##:::: ##:. ######::. ######:::. #######:: ##::. ##:",
		"..:::::::::..:::::..:::......::::......:::::.......:::..::::..::"
	};
	int aboutScreenPrintSpot = defaultConsoleSize.X/2 - title[0].length()/2;

	for(size_t i = 0; i < ABOUT_SCREEN_TITLE; ++i)
	{
		gotoXY(aboutScreenPrintSpot, 6 + i);
		cout << title[i];
	}
	const size_t ABOUT_MENU_DETAILS = 5;
	string aboutMenuDetails[ABOUT_MENU_DETAILS] =
	{
		" This game is brought to you by Team 11     ",
		"       Members :   Tng Kah Wei              ",
		"                   Leng Wei Shao, Sean      ",
		"                   Rayner Tay Yi Zhe        ",
		"                   Koh Tim Lin              "
	};

	int aboutMenuDetailsPrintSpot = consoleSize.X/2 - aboutMenuDetails[0].length()/2;

	for(size_t i = 0; i < ABOUT_MENU_DETAILS; ++i)
	{
		gotoXY(aboutMenuDetailsPrintSpot, 17 + i);
		cout << aboutMenuDetails[i];
	}

	gotoXY(60, 17 + ABOUT_MENU_DETAILS);

	pressToContinue(20 + ABOUT_MENU_DETAILS);
}

void customGame(string mapName)
{
	mapName = "Custom Maps/" + mapName;
	Loadables tempLoads(0,3,0);

	customLevelLoop(mapName, tempLoads);
}