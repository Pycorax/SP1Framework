#include "saves.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <string>
#include "Framework/console.h"

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

	ofstream saveFile;
	bool needOverwrite = false;
	string directory = "Saves/";
	string fullFileName = directory + saveName + ".sav";

	if(fileExists(fullFileName))
	{
		needOverwrite = true;
	}

	saveFile.open(fullFileName.c_str());

	if(saveFile.is_open())
	{
		if(needOverwrite)
		{
			string qnOverwrite = "A save file already exists. Do you want to overwrite it?";
			gotoXY(consoleSize.X/2 - qnOverwrite.length()/2, 25);
			cout << qnOverwrite;

			const size_t SAVE_MENU_OPTIONS = 8;
			string saveMenuOptions[SAVE_MENU_OPTIONS] =
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

			int saveMenuOptionsPrintSpot = consoleSize.X/2 - saveMenuOptions[0].length()/2;

			for(size_t i = 0; i < SAVE_MENU_OPTIONS; ++i)
			{
				gotoXY(saveMenuOptionsPrintSpot, 27 + i);
				cout << saveMenuOptions[i];
			}

			gotoXY(consoleSize.X/2, 29 + SAVE_MENU_OPTIONS);

			bool resume = true;
			while(resume)
			{
				switch(_getch())
				{
				case'1':
					resume = false;
					break;
				case'2':
					cout << "Failed to save game!" << endl;
					return false;
					break;
				}
			}
		}

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

bool fileExists(string saveName)
{
	ifstream file;

	file.open(saveName.c_str());

	if(file.is_open())
	{
		string firstLine;
		getline(file, firstLine);
		file.close();

		if(firstLine == "")
		{
			return false;
		}
		else
		{
			return true;
		}
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
	system("dir \"Saves\" /b /a-d *.sav > file_names");

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
	system("dir \"Saves\" /b /a-d *.sav > file_names");

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