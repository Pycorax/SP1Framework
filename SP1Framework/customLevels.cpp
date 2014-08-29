#include "customLevels.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::getline;

int findCustomMaps(vector<string> &fileNames)
{
	short numOfFiles = 0;
	ifstream files;

	//Gets all file names
	system("dir \"Custom Maps\\*.map\" /b /a-d > map_names");

	files.open("map_names");

	if(files.is_open())
	{
		string output;

		while(!files.eof())
		{
			getline(files,output);
			if (!(output == ""))
			{
				output = output.substr(0,output.length() - 4);	//Gets rid of file extension
				fileNames.push_back(output);
				++numOfFiles;
			}
		}

		files.close();

		remove("map_names");
	}
	else
	{
		cout << "Error checking for available files!";
		return -1;
	}

	return numOfFiles;
}

int findCustomMaps()
{
	short numOfFiles = 0;
	ifstream files;

	//Gets all file names
	system("dir \"Custom Maps\\*.map\" /b /a-d > map_names");

	files.open("map_names");

	if(files.is_open())
	{
		string output;

		while(!files.eof())
		{
			getline(files,output);
			if (output != "")
			{
				++numOfFiles;
			}
		}

		files.close();

		remove("map_names");
	}
	else
	{
		cout << "Error checking for available files!";
		return -1;
	}

	return numOfFiles;
}