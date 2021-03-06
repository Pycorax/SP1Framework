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

	colour(getColourWORD(E_WHITE_COLOR));

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

	const size_t MAIN_MENU_OPTIONS = 15;
	string mainMenuOptions[MAIN_MENU_OPTIONS] =
	{
		" __________________________",
		"|                          |", //Total Length 20
		"|                          |",
		"|      Start Game          |",
		"|      Load Saves          |",
		"|      Play Custom         |",
		"|      Game Guide          |",
		"|      Custom Game Guide   |",
		"|      Del Saves           |",
		"|      High Scores         |",
		"|      Options             |",
		"|      About               |",
		"|      Exit Game           |",
		"|                          |",
		"|__________________________|"
	};

	int mainMenuOptionsPrintSpot = defaultConsoleSize.X/2 - mainMenuOptions[0].length()/2;

	for(size_t i = 0; i < MAIN_MENU_OPTIONS; ++i)
	{
		gotoXY(mainMenuOptionsPrintSpot, 17 + i);
		cout << mainMenuOptions[i];
	}

	printControls();

	string recommendedFont = "Best played at Raster 8x8 font size!";
	gotoXY(defaultConsoleSize.X/2 - recommendedFont.length()/2, 30 + MAIN_MENU_OPTIONS);
	cout << recommendedFont;

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
		else if(keyPressed[E_DOWN_KEY] && selection < 9)
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
					game = E_CUSTOM_GAME_GUIDE;
					break;
				case 5:
					game = E_DELETE_SAVES;
					break;
				case 6:
					game = E_HIGH_SCORES;
					break;
				case 7:
					game = E_OPTIONS_MENU;
					break;
				case 8:
					game = E_ABOUT_SCREEN;
					break;
				case 9:
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

void drawPacman(int x, int y)
{
	static bool even = true;

	if(even)
		{
			gotoXY(x, y);
			cout << "___";
			gotoXY(x, y + 1);
			cout << "(*<";
			even = false;
		}
		else
		{
			gotoXY(x, y);
			cout << "___";
			gotoXY(x, y + 1);
			cout << "(*=";
			even = true;
		}
}

void gameGuide(GAMESTATE &game)
{
	//consoleSize = consoleSize;
	//setConsoleSize;
	colour(getColourWORD(E_WHITE_COLOR));
	extern bool keyPressed[E_MAX_KEYS];
		

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

	const size_t GAME_INSTRUCTIONS = 8;
	string gameInstructions[GAME_INSTRUCTIONS] =
	{
		"	                                  ",
		"HOW TO PLAY?",
		"	1: Use Arrow Keys to move the Pacman around & Space Bar to shoot",
		"	2: Collect all pellets or reach the minimum score to go to the next level",
		"	3: Kill Ghosts or collect pellets to gain score",
		"	4: Touching ghosts = death",
		"	5: Press the Esc key anytime during the game to pause the game where you can save or exit the game"
	};

	int gameguideprintSpots = consoleSize.X/2 - gameguideMenu[0].length()/2;

	for(size_t a = 0; a < GAME_GUIDE_MENU; ++a)
	{
		gotoXY(gameguideprintSpots, 2 + a);
		cout << gameguideMenu[a];
	}

	for(size_t b = 0; b < GAME_INSTRUCTIONS; ++b)
	{
		gotoXY(13, 2 + GAME_GUIDE_MENU + b);
		cout << gameInstructions[b] << endl;
	}

	colour(getColourWORD(E_WHITE_COLOR));
	cout << "             GHOSTS" << endl;
	colour(FOREGROUND_GREEN);
	cout << endl;
	cout << "                 /1\\" << endl;
	cout << "                 o-o " << endl;
	cout << "                 vvv " << endl;

	colour(FOREGROUND_RED | FOREGROUND_BLUE);
	cout << endl;
	cout << "                 /2\\" << endl;
	cout << "                 o-o" << endl;
	cout << "                 vvv" << endl;

	colour(FOREGROUND_RED);
	cout << endl;
	cout << "                 [3]" << endl;
	cout << "                 O-O" << endl;
	cout << "                 vvv" << endl;

	cout << endl;
	colour(getColourWORD(E_WHITE_COLOR));
	cout << "             PowerUps" << endl;

	char bullSpeed = 15;
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << endl;
	cout << "                 " << bullSpeed << endl;

	unsigned char scoreMult = 228;
	colour(getColourWORD(E_LIGHT_GREEN_COLOR));
	cout << "                 " << scoreMult << endl;

	char bullDmg = 30;
	colour(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "                 " << bullDmg << endl;

	char heartShape = 3;
	colour(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "                 " << heartShape << " = Gives Pacman Additional Life " << endl;

	colour(getColourWORD(E_WHITE_COLOR));
	//Ghost 1
	gotoXY(23, 20);
	cout << "Level: 1";

	gotoXY(23, 21);
	cout << "Damage: 1";

	gotoXY(23, 22);
	cout << "Health: 1";

	//Ghost 2
	gotoXY(23, 24);
	cout << "Level: 2";

	gotoXY(23, 25);
	cout << "Damage: 1";

	gotoXY(23, 26);
	cout << "Health: 2";

	//Ghost 3
	gotoXY(23, 28);
	cout << "Level: 2";

	gotoXY(23, 29);
	cout << "Damage: 1";

	gotoXY(23, 30);
	cout << "Health: 2";

	//Powerups
	gotoXY(19, 34);
	cout << "= Increases Bullet Movement Speed";

	gotoXY(19, 35);
	cout << "= Score Multiplier 2X";

	gotoXY(19, 36);
	cout << "= Increase Bullet Damage";

	gotoXY(19, 37);
	cout << "= Gives Pacman Additional Life";

	gotoXY(17,39);
	cout << "Your character will blink the colour of the power up you picked up!";

	colour(getColourWORD(E_WHITE_COLOR));
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "             PACMAN" << endl;
	//Pacman
	gotoXY(17, 44);
	colour(getColourWORD(E_WHITE_COLOR));
	cout << "      Damage: 1";

	colour(getColourWORD(E_WHITE_COLOR));

	string continueText = "Press Up to Continue...";
	gotoXY(consoleSize.X/2 - continueText.length()/2, 50);
	cout << continueText;

	gotoXY(consoleSize.X/2, 52);

	while(true)
	{
		colour(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		drawPacman(17, 43);
		Sleep(100);
		getInput();

		if ( keyPressed[E_UP_KEY] )
		{
			game = E_MAIN_MENU;
			break;
		}
	}
}

void gameOver(GAMESTATE &game)
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	
	printBorder();

	colour(getColourWORD(E_WHITE_COLOR));

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
		switch(_getch())
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

void gameLoop(string maps[], const size_t NUM_OF_MAPS, GAMESTATE &game, Loadables &loads, OptionSet options)
{
	for(size_t currentLevel = loads.level; currentLevel < NUM_OF_MAPS; ++currentLevel)
	{
		if(game == E_GAME)
		{
			levelLoop(maps[currentLevel], game, currentLevel, loads, options);
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
	extern bool keyPressed[E_MAX_KEYS];
	int selection = 0;
	int oldSelection = 0;
	bool selectionChanged = false;

	int numOfSaves = findSaveFiles();

	colour(getColourWORD(E_WHITE_COLOR));
	cls();

	colour(getColourWORD(E_WHITE_COLOR));

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

			colour(getColourWORD(E_WHITE_COLOR));
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
			" _____________ ",
			"|             |", //Total Length 20
			"|             |",
			"|      Yes    |",
			"|             |",
			"|      No     |",
			"|             |",
			"|_____________|"
		};

		int cantSaveOptionsPrintSpot = consoleSize.X/2 - cantSaveOptions[0].length()/2;

		for(size_t i = 0; i < CANT_SAVE_OPTIONS; ++i)
		{
			gotoXY(cantSaveOptionsPrintSpot, 18 + SAVE_MENU_TITLE + i);
			cout << cantSaveOptions[i];
		}

		printControls();

		//New Menu System
		gotoXY(consoleSize.X/2 - cantSaveOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 29 + selection);
		cout << g_MENU_TICKER;

		bool resume = true;
		while(resume)
		{
			gotoXY(consoleSize.X/2, 27 + 4 + CANT_SAVE_OPTIONS);
			selectionChanged = false;
			getInput();

			if(keyPressed[E_UP_KEY] && selection > 0)
			{
				oldSelection = selection;
				--selection;
				if(selection == 1)
				{
					--selection;
				}
				selectionChanged = true;
			}
			else if(keyPressed[E_DOWN_KEY] && selection < 2)
			{
				oldSelection = selection;
				++selection;
				if(selection == 1)
				{
					++selection;
				}
				selectionChanged = true;
			}
			else if(keyPressed[E_SPACE_KEY])
			{
				switch(selection)
				{
					case 0:
						if(deleteMenu())
						{
							saveMenu(loads);
						}
						resume = false;
						break;
					case 2:
						resume = false;
						break;
				}
			}

			if(selectionChanged)
			{

				gotoXY(consoleSize.X/2 - cantSaveOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 29 + oldSelection);
				cout << " ";
				gotoXY(consoleSize.X/2 - cantSaveOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 29 + selection);
				cout << g_MENU_TICKER;
			}
			Sleep(100);
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
	
	unsigned short maxSaveNameLength = 6; //Length of "Return"

	//Get longest save name
	for(size_t i = 0; i < listOfLevels.size(); ++i)
	{
		if(listOfLevels[i].length() >  maxSaveNameLength)
		{
			 maxSaveNameLength = listOfLevels[i].length();
		}
	}

	printBorder();

	colour(getColourWORD(E_WHITE_COLOR));

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

	int numOfSaves = 0;
	bool saveFilesPresent = false;
	for(size_t i = 0; i < listOfLevels.size(); ++i)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23 + numOfSaves);
		cout << listOfLevels[numOfSaves];
		++numOfSaves;

		saveFilesPresent = true;
	}

	size_t saveFilesToPrint = numOfSaves;

	if(!saveFilesPresent)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23);
		cout << "No Saves";
		saveFilesToPrint = 2;
	}

	//Draws Border
	//--Top
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19);
	for(size_t i = 0; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Bottom
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + saveFilesToPrint);
	for(size_t i = 0; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Left
	for(size_t i = 1; i < saveFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length() - 2, 19 + i);
		cout << "|";
	}
	//--Right
	for(size_t i = 1; i < saveFilesToPrint + 5; ++i)
	{
		gotoXY(consoleSize.X/2 + maxSaveNameLength/2 + g_MENU_TICKER.length() + 2, 19 + i);
		cout << "|";
	}
	
	printControls();

	//New Menu
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
		else if(keyPressed[E_DOWN_KEY] && selection + 1 < numOfSaves)
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

	colour(getColourWORD(E_WHITE_COLOR));
	cls();

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

	printControls();

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

	return false;
}

void loadingScreen(string mapName)
{
	colour(getColourWORD(E_WHITE_COLOR));
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

void startScreen(string mapName, int level)
{
	cls();
	colour(getColourWORD(E_WHITE_COLOR));
	const size_t START_SCREEN_TITLE = 8;
	string startscreen[START_SCREEN_TITLE] =
	{
		"  '##:::::::'########:'##::::'##:'########:'##:::::::::",
        "   ##::::::: ##.....:: ##:::: ##: ##.....:: ##:::::::::",
        "   ##::::::: ##::::::: ##:::: ##: ##::::::: ##:::::::::",
        "   ##::::::: ######::: ##:::: ##: ######::: ##:::::::::",
        "   ##::::::: ##...::::. ##:: ##:: ##...:::: ##:::::::::",
        "   ##::::::: ##::::::::. ## ##::: ##::::::: ##:::::::::",
        "   ########: ########:::. ###:::: ########: ########:::",
        "  ........::........:::::...:::::........::........::::"

	};

	const size_t SPACE_SCREEN = 8;
	string space[SPACE_SCREEN] =
	{
		"  ",
        "  ",
        "  ",
        "  ",
        "  ",
        "  ",
        "  ",
        "  "
	};

	const size_t DIGIT_HEIGHT = 8;
	const size_t NUM_OF_DIGITS = 10;
	string levelscreen[NUM_OF_DIGITS][DIGIT_HEIGHT] =
	{
		{
		   "::'#####:::",
		   ":'##.. ##::",
		   "'##:::: ##:",
		   " ##:::: ##:",
		   " ##:::: ##:",
		   ". ##:: ##::",
		   ":. #####:::",
		   "::.....::::",
		},

		{
		   ":::'##:::",
		   ":'####:::",
		   ":.. ##:::",
		   "::: ##:::",
		   "::: ##:::",
		   "::: ##:::",
		   ":'######:",
		   ":......::",
	    },
		   
		{
		   ":'#######::",
		   "'##.... ##:",
		   "..::::: ##:",
		   ":'#######::",
		   "'##::::::::",
		   " ##::::::::",
		   " #########:",
		   ".........::",
		},

		{
			":'#######::",
			"'##.... ##:",
			"..::::: ##:",
			":'#######::",
			":...... ##:",
			"'##:::: ##:",
			". #######::",
			":.......:::",
		},

		{
			"'##::::::::",
			" ##:::'##::",
			" ##::: ##::",
			" ##::: ##::",
			" #########:",
			"...... ##::",
			":::::: ##::",
			"::::::..:::",
		},

		{
			"'########:",
			" ##.....::",
			" ##:::::::",
			" #######::",
			"...... ##:",
			"'##::: ##:",
			". ######::",
			":......:::",
		},
			   
		{

			":'#######::",
			"'##.... ##:",
			" ##::::..::",
			" ########::",
			" ##.... ##:",
			" ##:::: ##:",
			". #######::",
			":.......:::",
		},

		{
			"'########:",
			" ##..  ##:",
			"..:: ##:::",
			"::: ##::::",
			":: ##:::::",
			":: ##:::::",
			":: ##:::::",
			"::..::::::",
		},
			
		{
			":'#######::",
			"'##.... ##:",
			" ##:::: ##:",
			": #######::",
			"'##.... ##:",
			" ##:::: ##:",
			". #######::",
			":.......:::",
		},

		{
			":'#######::",
			"'##.... ##:",
			" ##:::: ##:",
			": ########:",
			":...... ##:",
			"'##:::: ##:",
			". #######::",
			":.......:::",
		},
	};
	
	//Code for appending number to the end
	if (level > 9)
	{
		short firstDigit = level/10;
		short secondDigit = level%10;
		for(int i = 0; i < START_SCREEN_TITLE; ++i)
		{
			startscreen[i] += space[i];
			startscreen[i] += levelscreen[firstDigit][i];
			startscreen[i] += levelscreen[secondDigit][i];
		}
	}
	else
	{
		for(int i = 0; i < START_SCREEN_TITLE; ++i)
		{
			startscreen[i] += space[i];
			startscreen[i] += levelscreen[level][i];
		}
	}

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
	colour(getColourWORD(E_WHITE_COLOR));
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
	colour(getBGColourWORD(E_BLACK_BG_COLOR));
	cls();
	colour(getColourWORD(E_WHITE_COLOR));
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

	colour(getColourWORD(E_WHITE_COLOR));
	cls();

	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

	printBorder();

	colour(getColourWORD(E_WHITE_COLOR));
	
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

	printControls();

	//New Menu
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

		size_t maxSaveNameLength = 6; //Length of "return"
		
		//Get longest map name
		for(size_t i = 0; i < listOfLevels.size(); ++i)
		{
			if(listOfLevels[i].length() >  maxSaveNameLength)
			{
				maxSaveNameLength = listOfLevels[i].length();
			}
		}

		colour(getColourWORD(E_WHITE_COLOR));
		cls();

		printBorder();
		colour(getColourWORD(E_WHITE_COLOR));

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

		int numOfSaves = 0;
		bool saveFilesPresent = false;
		for(size_t i = 0; i < listOfLevels.size(); ++i)
		{
			gotoXY(loadMenuOptionsPrintSpot, 23 + numOfSaves);
			cout << listOfLevels[numOfSaves];
			++numOfSaves;

			saveFilesPresent = true;
		}

		size_t saveFilesToPrint = numOfSaves;

		if(!saveFilesPresent)
		{
			gotoXY(loadMenuOptionsPrintSpot, 23);
			cout << "No Saves";
			saveFilesToPrint = 2;
		}

		//Draws Border
		//--Top
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19);
		for(size_t i = 0; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
		{
			cout << "_";
		}
		//--Bottom
		gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + saveFilesToPrint);
		for(size_t i = 0; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
		{
			cout << "_";
		}
		//--Left
		for(size_t i = 1; i < saveFilesToPrint + 5; ++i)
		{
			gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - g_MENU_TICKER.length() - 2, 19 + i);
			cout << "|";
		}
		//--Right
		for(size_t i = 1; i < saveFilesToPrint + 5; ++i)
		{
			gotoXY(consoleSize.X/2 + maxSaveNameLength/2 + g_MENU_TICKER.length() + 2, 19 + i);
			cout << "|";
		}

		printControls();

		//New Menu
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

	size_t maxSaveNameLength = 6; //Length of "return"

	//Get longest map name
	for(size_t i = 0; i < listOfLevels.size(); ++i)
	{
		if(listOfLevels[i].length() >  maxSaveNameLength)
		{
			maxSaveNameLength = listOfLevels[i].length();
		}
	}

	colour(getColourWORD(E_WHITE_COLOR));
	cls();

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

	int numOfSaves = 0;
	bool saveFilesPresent = false;
	for(size_t i = 0; i < listOfLevels.size(); ++i)
	{
		gotoXY(loadMenuOptionsPrintSpot, 23 + numOfSaves);
		cout << listOfLevels[numOfSaves];
		++numOfSaves;

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
	for(size_t i = 0; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
	{
		cout << "_";
	}
	//--Bottom
	gotoXY(consoleSize.X/2 - maxSaveNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + saveFilesToPrint);
	for(size_t i = 0; i < maxSaveNameLength + (g_MENU_TICKER.length() + 1) * 2 + 1; ++i)
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

	printControls();

	//New Menu
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
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

	const int VICTORY_SCREEN_SIZE = 12;
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
		"               CONGRATULATIONS ON COMPLETING THIS LEVEL              ",
		"",
		"                     You have gained another life!                  "
	};

	colour(getColourWORD(E_WHITE_COLOR));
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
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

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

	colour(getColourWORD(E_WHITE_COLOR));
	cls();
	for(int a = 0; a < LOSE_SCREEN_SIZE; ++a)
	{
		gotoXY(consoleSize.X/2 - loseScreen[a].length()/2, 10 + a);
		cout << loseScreen[a];
	}

	pressToContinue(17 + LOSE_SCREEN_SIZE);
}

void loadCustomLevelMenu(GAMESTATE &game, OptionSet options)
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

	extern bool keyPressed[E_MAX_KEYS];

	int selection = -1;
	int oldSelection = -1;
	bool selectionChanged = false;
	vector<string> listOfCustomMaps;
	findCustomMaps(listOfCustomMaps);

	size_t maxMapNameLength = 6; //Length of "Return"

	//Get longest map name
	for(size_t i = 0; i < listOfCustomMaps.size(); ++i)
	{
		if(listOfCustomMaps[i].length() > maxMapNameLength)
		{
			maxMapNameLength = listOfCustomMaps[i].length();
		}
	}

	printBorder();
	colour(getColourWORD(E_WHITE_COLOR));

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

	int numOfMaps = 0;
	bool mapFilesPresent = false;
	for(size_t i = 0; i < listOfCustomMaps.size(); ++i)
	{
		gotoXY(customMapsMenuOptionsPrintSpot, 23 + numOfMaps);
		cout << listOfCustomMaps[numOfMaps];

		++numOfMaps;

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
	for(size_t i = 1; i < maxMapNameLength + (g_MENU_TICKER.length() + 1) * 2; ++i)
	{
		cout << "_";
	}
	//--Bottom
	gotoXY(consoleSize.X/2 - maxMapNameLength/2 - 1 - g_MENU_TICKER.length(), 19 + 4 + mapFilesToPrint);
	for(size_t i = 1; i < maxMapNameLength + (g_MENU_TICKER.length() + 1) * 2; ++i)
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

	printControls();

	//New Menu
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
				customGame(listOfCustomMaps[selection], options);
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

	colour(getColourWORD(E_WHITE_COLOR));
	cls();
	
	const size_t ABOUT_SCREEN_TITLE = 8;
	string title[ABOUT_SCREEN_TITLE] =
	{
		":::'###::::'########:::'#######::'##::::'##:'########:",
		"::'## ##::: ##.... ##:'##.... ##: ##:::: ##:... ##..::",
		":'##:. ##:: ##:::: ##: ##:::: ##: ##:::: ##:::: ##::::",
		"'##:::. ##: ########:: ##:::: ##: ##:::: ##:::: ##::::",
		" #########: ##.... ##: ##:::: ##: ##:::: ##:::: ##::::",
		" ##.... ##: ##:::: ##: ##:::: ##: ##:::: ##:::: ##::::",
		" ##:::: ##: ########::. #######::. #######::::: ##::::",
		"..:::::..::........::::.......::::.......::::::..:::::"
	};
	int aboutScreenPrintSpot = defaultConsoleSize.X/2 - title[0].length()/2;

	for(size_t i = 0; i < ABOUT_SCREEN_TITLE; ++i)
	{
		gotoXY(aboutScreenPrintSpot, 6 + i);
		cout << title[i];
	}
	const size_t ABOUT_MENU_DETAILS = 6;
	string aboutMenuDetails[ABOUT_MENU_DETAILS] =
	{
		" This game is brought to you by Team 11     ",
		"",
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

void customGame(string mapName, OptionSet options)
{
	mapName = "Custom Maps/" + mapName;
	Loadables tempLoads(0,3,0);

	customLevelLoop(mapName, tempLoads, options);
}

void optionsMenu(GAMESTATE &game, OptionSet &options)
{
	extern bool keyPressed[E_MAX_KEYS];
	int selection = 0;
	int oldSelection = 0;
	bool selectionChanged = false;
	const short NUM_OF_OPTIONS = 6;
	bool colourChanged[NUM_OF_OPTIONS];

	string errorSaving = "Unable to save changes!";

	OptionSet newOptions = options;

	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_BLUE);
	cls();
	printBorder();

	colour(getColourWORD(E_WHITE_COLOR));

	const size_t OPTIONS_MENU_TITLE = 8;
	string optionsMenuTitle[OPTIONS_MENU_TITLE] = 
	{
		"'########:::::'###:::::'######:::'######:::'##::::'##:'##::: ##:", //Replace with OPTIONS
		" ##.... ##:::'## ##:::'##... ##:'##... ##:: ##:::: ##: ###:: ##:", 
		" ##:::: ##::'##:. ##:: ##:::..:: ##:::..::: ##:::: ##: ####: ##:", //Total Length = 64
		" ########::'##:::. ##: ##::::::: ##::'####: ##:::: ##: ## ## ##:",
		" ##.....::: #########: ##::::::: ##::: ##:: ##:::: ##: ##. ####:",
		" ##:::::::: ##.... ##: ##::: ##: ##::: ##:: ##:::: ##: ##:. ###:",
		" ##:::::::: ##:::: ##:. ######::. ######:::. #######:: ##::. ##:",
		"..:::::::::..:::::..:::......::::......:::::.......:::..::::..::"
	};

	int optionsMenuTitlePrintSpot = defaultConsoleSize.X/2 - optionsMenuTitle[0].length()/2;

	for(size_t i = 0; i < OPTIONS_MENU_TITLE; ++i)
	{
		gotoXY(optionsMenuTitlePrintSpot, 6 + i);
		cout << optionsMenuTitle[i];
	}

	const size_t OPTIONS_MENU_OPTIONS = 15;
	string optionsMenuOptions[OPTIONS_MENU_OPTIONS] =
	{
		" _______________________",
		"|                       |", //Total Length 20
		"|                       |",
		"|      Player Colour    |",
		"|      Bullet Colour    |",
		"|      Wall Colour      |",
		"|      Pellet Colour    |",
		"|                       |",
		"|      HUD Text Colour  |",
		"|      HUD BG Colour    |",
		"|                       |",
		"|      Save Changes     |",
		"|      Cancel           |",
		"|                       |",
		"|_______________________|"
	};

	int mainMenuOptionsPrintSpot = defaultConsoleSize.X/2 - optionsMenuOptions[0].length()/2;

	for(size_t i = 0; i < OPTIONS_MENU_OPTIONS; ++i)
	{
		colour(getColourWORD(E_WHITE_COLOR));
		gotoXY(mainMenuOptionsPrintSpot, 17 + i);
		cout << optionsMenuOptions[i];

		switch(i)
		{
			case 3:
				gotoXY(mainMenuOptionsPrintSpot + 7, 17 + i);
				colour(getColourWORD(options.playerColour));
				cout << "Player Colour";
				break;
			case 4:
				gotoXY(mainMenuOptionsPrintSpot + 7, 17 + i);
				colour(getColourWORD(options.bulletColour));
				cout << "Bullet Colour";
				break;
			case 5:
				gotoXY(mainMenuOptionsPrintSpot + 7, 17 + i);
				colour(getColourWORD(options.wallColour));
				cout << "Wall Colour";
				break;
			case 6:
				gotoXY(mainMenuOptionsPrintSpot + 7, 17 + i);
				colour(getColourWORD(options.pelletColour));
				cout << "Pellet Colour";
				break;
			case 8:
				gotoXY(mainMenuOptionsPrintSpot + 7, 17 + i);
				colour(getColourWORD(options.hudTextColour));
				cout << "HUD Text Colour";
				break;
			case 9:
				gotoXY(mainMenuOptionsPrintSpot + 7, 17 + i);
				colour(getBGColourWORD(options.hudBGColour));
				cout << "HUD BG Colour";
				break;
		}
	}

	printOptionsControls();

	//New Menu System
	gotoXY(consoleSize.X/2 - optionsMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
	cout << g_MENU_TICKER;

	while(game == E_OPTIONS_MENU)
	{
		gotoXY(consoleSize.X/2, 17 + 4 + OPTIONS_MENU_OPTIONS);
		selectionChanged = false;
		
		for (short i = 0; i < NUM_OF_OPTIONS; ++i)
		{
			colourChanged[i] = false;
		}

		getInput();

		for (int i = 0; i < E_MAX_KEYS; ++i)
		{
			if (keyPressed[i])
			{
				gotoXY(consoleSize.X/2 - errorSaving.length()/2, 32);
				
				for (size_t j = 0; j < errorSaving.length(); ++j)
				{
					cout << " ";
				}
			}
		}

		if(keyPressed[E_UP_KEY] && selection > 0)
		{
			oldSelection = selection;
			--selection;
			if(selection == 4 || selection == 7)
			{
				--selection;
			}
			selectionChanged = true;
		}
		else if(keyPressed[E_DOWN_KEY] && selection < 9)
		{
			oldSelection = selection;
			++selection;
			if(selection == 4 || selection == 7)
			{
				++selection;
			}
			selectionChanged = true;
		}
		else if(keyPressed[E_LEFT_KEY])
		{
			switch(selection)
			{
				case 0:
					if(newOptions.playerColour == 0)
					{
						newOptions.playerColour = static_cast<COLOR>(E_MAX_COLORS - 1);
					}
					else
					{
						newOptions.playerColour = static_cast<COLOR>(newOptions.playerColour - 1);
					}
					colourChanged[0] = true;
					break;
				case 1:
					if(newOptions.bulletColour == 0)
					{
						newOptions.bulletColour = static_cast<COLOR>(E_MAX_COLORS - 1);
					}
					else
					{
						newOptions.bulletColour = static_cast<COLOR>(newOptions.bulletColour - 1);
					}
					colourChanged[1] = true;
					break;
				case 2:
					if(newOptions.wallColour == 0)
					{
						newOptions.wallColour = static_cast<COLOR>(E_MAX_COLORS - 1);
					}
					else
					{
						newOptions.wallColour = static_cast<COLOR>(newOptions.wallColour - 1);
					}
					colourChanged[2] = true;
					break;
				case 3:
					if(newOptions.pelletColour == 0)
					{
						newOptions.pelletColour = static_cast<COLOR>(E_MAX_COLORS - 1);
					}
					else
					{
						newOptions.pelletColour = static_cast<COLOR>(newOptions.pelletColour - 1);
					}
					colourChanged[3] = true;
					break;
				case 5:
					if(newOptions.hudTextColour == 0)
					{
						newOptions.hudTextColour = static_cast<COLOR>(E_MAX_COLORS - 1);
					}
					else
					{
						newOptions.hudTextColour = static_cast<COLOR>(newOptions.hudTextColour - 1);
					}
					colourChanged[4] = true;
					break;
				case 6:
					if(newOptions.hudBGColour == 0)
					{
						newOptions.hudBGColour = static_cast<BG_COLOR>(E_MAX_BG_COLORS - 1);
					}
					else
					{
						newOptions.hudBGColour = static_cast<BG_COLOR>(newOptions.hudBGColour - 1);
					}
					colourChanged[5] = true;
					break;
			}
		}
		else if(keyPressed[E_RIGHT_KEY])
		{
			switch(selection)
			{
			case 0:
				if(newOptions.playerColour == E_MAX_COLORS - 1)
				{
					newOptions.playerColour = static_cast<COLOR>(0);
				}
				else
				{
					newOptions.playerColour = static_cast<COLOR>(newOptions.playerColour + 1);
				}
				colourChanged[0] = true;
				break;
			case 1:
				if(newOptions.bulletColour == E_MAX_COLORS - 1)
				{
					newOptions.bulletColour = static_cast<COLOR>(0);
				}
				else
				{
					newOptions.bulletColour = static_cast<COLOR>(newOptions.bulletColour + 1);
				}
				colourChanged[1] = true;
				break;
			case 2:
				if(newOptions.wallColour == E_MAX_COLORS - 1)
				{
					newOptions.wallColour = static_cast<COLOR>(0);
				}
				else
				{
					newOptions.wallColour = static_cast<COLOR>(newOptions.wallColour + 1);
				}
				colourChanged[2] = true;
				break;
			case 3:
				if(newOptions.pelletColour == E_MAX_COLORS - 1)
				{
					newOptions.pelletColour = static_cast<COLOR>(0);
				}
				else
				{
					newOptions.pelletColour = static_cast<COLOR>(newOptions.pelletColour + 1);
				}
				colourChanged[3] = true;
				break;
			case 5:
				if(newOptions.hudTextColour == E_MAX_COLORS - 1)
				{
					newOptions.hudTextColour = static_cast<COLOR>(0);
				}
				else
				{
					newOptions.hudTextColour = static_cast<COLOR>(newOptions.hudTextColour + 1);
				}
				colourChanged[4] = true;
				break;
			case 6:
				if(newOptions.hudBGColour == E_MAX_BG_COLORS - 1)
				{
					newOptions.hudBGColour = static_cast<BG_COLOR>(0);
				}
				else
				{
					newOptions.hudBGColour = static_cast<BG_COLOR>(newOptions.hudBGColour + 1);
				}
				colourChanged[5] = true;
				break;
			}
		}
		else if(keyPressed[E_SPACE_KEY])
		{
			switch(selection)
			{
				case 8:
					if(saveOptions(options, newOptions))
					{
						game = E_MAIN_MENU;
					}
					else
					{
						gotoXY(consoleSize.X/2 - errorSaving.length()/2, 32);
						cout << errorSaving;
						game = E_OPTIONS_MENU;
					}
					break;
				case 9:
					game = E_MAIN_MENU;
					break;
				default:
					game = E_OPTIONS_MENU;
					break;
			}
		}

		if(selectionChanged)
		{
			gotoXY(consoleSize.X/2 - optionsMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + oldSelection);
			cout << " ";
			gotoXY(consoleSize.X/2 - optionsMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 20 + selection);
			cout << g_MENU_TICKER;
		}

		for (short i = 0; i < NUM_OF_OPTIONS; ++i)
		{
			if(colourChanged[i])
			{
				switch(i)
				{
					case 0:
						colour(getColourWORD(newOptions.playerColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 20);
						cout << "Player Colour";
						break;
					case 1:
						colour(getColourWORD(newOptions.bulletColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 21);
						cout << "Bullet Colour";
						break;
					case 2:
						colour(getColourWORD(newOptions.wallColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 22);
						cout << "Wall Colour";
						break;
					case 3:
						colour(getColourWORD(newOptions.pelletColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 23);
						cout << "Pellet Colour";
						break;
					case 4:
						colour(getColourWORD(newOptions.hudTextColour) | getBGColourWORD(newOptions.hudBGColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 25);
						cout << "HUD Text Colour";
						colour(getBGColourWORD(newOptions.hudBGColour) | getColourWORD(newOptions.hudTextColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 26);
						cout << "HUD BG Colour";
						break;
					case 5:
						colour(getColourWORD(newOptions.hudTextColour) | getBGColourWORD(newOptions.hudBGColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 25);
						cout << "HUD Text Colour";
						colour(getBGColourWORD(newOptions.hudBGColour) | getColourWORD(newOptions.hudTextColour));
						gotoXY(mainMenuOptionsPrintSpot + 7, 26);
						cout << "HUD BG Colour";
						break;
				}

				colour(getColourWORD(E_WHITE_COLOR));
			}
		}

		Sleep(100);
	}
}

void customGameGuide(GAMESTATE &game)
{
	newSetConsoleSize(defaultConsoleSize);

	colour(getColourWORD(E_WHITE_COLOR));
	cls();

	const size_t ABOUT_SCREEN_TITLE = 8;
	string title[ABOUT_SCREEN_TITLE] =
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
	int aboutScreenPrintSpot = defaultConsoleSize.X/2 - title[0].length()/2;

	for(size_t i = 0; i < ABOUT_SCREEN_TITLE; ++i)
	{
		gotoXY(aboutScreenPrintSpot, 6 + i);
		cout << title[i];
	}
	const size_t ABOUT_MENU_DETAILS = 36;
	string aboutMenuDetails[ABOUT_MENU_DETAILS] =
	{
		"A Map is comprised of two files: - .map                                                    ",
		"                                 - .aimap                                                  ",
		"                                                                                           ",
		"Creating a map is in a \"What you see is what you get\" fashion!",
		"",
		".map file",
		"=============",
		"Header Portion",
		"- Excluded from the physical map.",
		"- Contains other map details.",
		"- Look at template.map in the Custom Games folder for map header information!",
		"'#' - Symbol for a wall.",
		"' ' - Symbol for empty space",
		"'P' - Symbol for player spawn point. Only 1 may exist on the map.",
		"'H' - Symbol for a extra life power up.",
		"'s' - Symbol for a increased bullet speed power up.",
		"'d' - Symbol for a increased bullet damage power up.",
		"'M' - Symbol for a 2x score multiplier power up.",
		"",
		".aimap file",
		"=============",
		"'#' - Symbol for a wall.",
		"' ' - Symbol for empty space.",
		"'1' to '9' - Symbol for zone where the ghost roams. Corresponds to a Ghost's Zone ID",
		"",
		"Mapping Rules",
		"=============",
		"- Map and AIMap size must be equal.",
		"- Zones specified in Map and AIMap files must be equal.",
		"- Zones specified and Zones used by Ghosts in Map file must be equal.",
		"- Number of Zones must be set.",
		"- A spawn point must be set and only 1 can be set.",
		"- A minimum score must be set and only 1 can be set.",
		"- There must be at least 1 pellet on the map.",
		"",
		"A template for creating maps is waiting for you in the Custom Maps folder!"
	};

	int aboutMenuDetailsPrintSpot = consoleSize.X/2 - aboutMenuDetails[0].length()/2;

	for(size_t i = 0; i < ABOUT_MENU_DETAILS; ++i)
	{
		gotoXY(aboutMenuDetailsPrintSpot, 17 + i);
		cout << aboutMenuDetails[i];
	}

	gotoXY(60, 17 + ABOUT_MENU_DETAILS);

	pressToContinue(20 + ABOUT_MENU_DETAILS);

	game = E_MAIN_MENU;
}