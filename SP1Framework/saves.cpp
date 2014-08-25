#include "saves.h"
#include <fstream>
#include <iostream>
#include <conio.h>

using std::ofstream;
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;

bool saveGame(unsigned int level, string saveName)
{
	ofstream saveFile;

	saveName += ".sav";
	saveFile.open(saveName.c_str());

	if(saveFile.is_open())
	{
		if(saveFile.good())
		{
			cout << "A save file already exists. Do you want to overwrite it? (Y/N)";

			if(toupper(getch()) == 'N')
			{
				saveFile.close();
				return false;
			}
		}
		saveFile << level << endl;
		
		saveFile.close();

		return true;
	}
	else
	{
		cout << "Failed to save game!" << endl;
		return false;
	}
}

int loadGame(unsigned int &level, string saveName)
{
	ifstream saveFile;

	saveFile.open(saveName.c_str(), fstream::in);

	if(saveFile.is_open() && saveFile.good())
	{
		cout << "All unsaved progress will be lost? Are you sure you want to load? (Y/N)";

		if(toupper(getch()) == 'Y')
		{
			string levelObtained;

			getline(saveFile, levelObtained);
			level = atoi(levelObtained.c_str());
			saveFile.close();
			
			return true;
		}
		else
		{
			saveFile.close();
			return false;
		}
	}
	else
	{
		cout << "Failed to load the game!" << endl;
		return false;
	}

}

int findSaveFiles(vector<string> &fileNames)
{
	short numOfFiles = 0;
	ifstream files;

	//Gets all file names
	system("dir /b /a-d *.sav > file_names");

	files.open("file_names");

	if(files.is_open())
	{
		string output;

		while(!files.eof())
		{
			getline(files,output);
			if (!(output == "file_names.txt" || output == ""))
			{
				fileNames.push_back(output);
				++numOfFiles;
			}
		}

		files.close();
	}
	else
	{
		cout << "Error checking for available files!";
		return -1;
	}

	return numOfFiles;
}