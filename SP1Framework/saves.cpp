#include "saves.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <string>
#include "Framework/console.h"
#include "game.h"
#include "scorePoints.h"
#include "otherHelperFunctions.h"

using std::ofstream;
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;
using std::string;
using std::remove;

Loadables::Loadables(unsigned int levelToStartFrom, int playerLivesToStartWith, int scoreToStartWith)
{
	level = levelToStartFrom;
	playerLives = playerLivesToStartWith;
	cumulativeScore = scoreToStartWith;
}

bool saveGame(Loadables loads, string saveName)
{
	extern COORD consoleSize;
	extern enum KEYS;

	extern bool keyPressed[E_MAX_KEYS];
	int selection = 0;
	int oldSelection = 0;
	bool selectionChanged = false;

	ofstream saveFile;
	bool needOverwrite = false;
	string directory = "Saves/";
	string fullFileName = directory + saveName + ".sav";

	if(fileExists(fullFileName))
	{
		needOverwrite = true;
	}

	if(needOverwrite)
	{
		string qnOverwrite = "A save file already exists. Do you want to overwrite it?";
		gotoXY(consoleSize.X/2 - qnOverwrite.length()/2, 25);
		cout << qnOverwrite;
		gotoXY(1, 26);
		for (int i = 1; i < consoleSize.X - 1; ++i)
		{
			cout << " ";
		}

		const size_t SAVE_MENU_OPTIONS = 8;
		string saveMenuOptions[SAVE_MENU_OPTIONS] =
		{
			" _____________ ",
			"|             |", //Total Length 15
			"|             |",
			"|      Yes    |",
			"|             |",
			"|      No     |",
			"|             |",
			"|_____________|"
		};

		int saveMenuOptionsPrintSpot = consoleSize.X/2 - saveMenuOptions[0].length()/2;

		for(size_t i = 0; i < SAVE_MENU_OPTIONS; ++i)
		{
			gotoXY(saveMenuOptionsPrintSpot, 27 + i);
			cout << saveMenuOptions[i];
		}

		//New Menu System
		gotoXY(consoleSize.X/2 - saveMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 30 + selection);
		cout << g_MENU_TICKER;

		bool resume = true;
		while(resume)
		{
			gotoXY(consoleSize.X/2, 27 + 4 + SAVE_MENU_OPTIONS);
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
					resume = false;
					break;
				case 2:
					//GOTOXY
					string fail = "Failed to save game!";
					gotoXY(consoleSize.X/2 - fail.length()/2, 36);
					cout << fail;
					pressToContinue(38);
					return false;
					break;
				}
			}

			if(selectionChanged)
			{

				gotoXY(consoleSize.X/2 - saveMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 30 + oldSelection);
				cout << " ";
				gotoXY(consoleSize.X/2 - saveMenuOptions[0].length()/2 - g_MENU_TICKER.length() + 7, 30 + selection);
				cout << g_MENU_TICKER;
			}
			Sleep(100);
		}
	}

	saveFile.open(fullFileName.c_str());
	if(saveFile.is_open())
	{
		saveFile << loads.level << endl;
		saveFile << loads.playerLives << endl;
		saveFile << loads.cumulativeScore << endl;
		saveFile.close();
		return true;
	}
	else
	{
		cout << "Failed to save game!" << endl;
		return false;
	}
}

int loadGame(Loadables &loadInfo, string saveName)
{
	ifstream saveFile;

	string directory = "Saves/";

	saveName = directory + saveName;

	saveFile.open(saveName.c_str(), fstream::in);

	if(saveFile.is_open() && saveFile.good())
	{
		string levelObtained;

		getline(saveFile, levelObtained);
		loadInfo.level = atoi(levelObtained.c_str());
		getline(saveFile, levelObtained);
		loadInfo.playerLives = atoi(levelObtained.c_str());
		getline(saveFile, levelObtained);
		loadInfo.cumulativeScore = atoi(levelObtained.c_str());
		saveFile.close();

		return true;
	}
	else
	{
		return false;
	}

}

int findSaveFiles(vector<string> &fileNames)
{
	short numOfFiles = 0;
	ifstream files;

	//Gets all file names
	system("dir \"Saves\\*.sav\" /b /a-d > file_names");

	files.open("file_names");

	if(files.is_open())
	{
		string output;

		while(!files.eof())
		{
			getline(files,output);
			if (!(output == ""))
			{
				fileNames.push_back(output);
				++numOfFiles;
			}
		}

		files.close();

		remove("file_names");
	}
	else
	{
		cout << "Error checking for available files!";
		return -1;
	}

	return numOfFiles;
}

int findSaveFiles()
{
	short numOfFiles = 0;
	ifstream files;

	//Gets all file names
	system("dir \"Saves\\*.sav\" /b /a-d > file_names");

	files.open("file_names");

	if(files.is_open())
	{
		string output;

		while(!files.eof())
		{
			getline(files,output);
			if (!(output == "file_names" || output == ""))
			{
				++numOfFiles;
			}
		}

		files.close();

		remove("file_names");
	}
	else
	{
		cout << "Error checking for available files!";
		return -1;
	}

	return numOfFiles;
}

bool deleteGame(string saveName)
{
	string directory = "Saves/";

	saveName = directory + saveName;

	if(remove(saveName.c_str()) != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}