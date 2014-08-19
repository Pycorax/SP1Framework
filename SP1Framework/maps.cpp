#include "maps.h"

bool processMap(const char mapName[], vector<vector<char>> &processedMap)
{
	string readLine;
	char readChar;

	ifstream mapFile;
	mapFile.open(mapName);

	if(mapFile.is_open())
	{
		for (int coord_y = 0; !mapFile.eof() ; ++coord_y)
		{
			getline(mapFile, readLine);
			
			vector<char> *ptr = new vector<char>;

			for (size_t coord_x = 0; coord_x < readLine.length() ; ++coord_x)
			{
				readChar = readLine[coord_x];
				ptr->push_back(readChar);
			}

			processedMap.push_back(*ptr);
		}

		mapFile.close();

		return true;
	}
	else
	{
		return false;
	}
}

void renderMap(vector<vector<char>> processedMap)
{
	const char border = 176;
	const char space = ' ';
	const char obstacle = 176;
	const char pellet = 'o';
	const size_t spriteHeight = 3;
	const size_t spriteWidth = 3;

	//Controls Rows
	for (size_t coord_y = 0; coord_y < processedMap.size(); ++coord_y)
	{
		//Controls height of each tile
		for (int j = 0; j < spriteHeight; ++j)
		{
			//Controls Columns
			for (size_t coord_x = 0; coord_x < processedMap[coord_y].size(); ++coord_x)
			{	
				//Controls width of each tile
				for (int i = 0; i < spriteWidth; ++i)
				{
					switch(processedMap[coord_y][coord_x])
					{
						case'#':
							cout << border;
							break;
						case'O':
							cout << obstacle;
							break;
						case '.':
							if (j == spriteWidth/2)
							{
								if(i == spriteWidth/2)
								{
									cout << pellet;
								}
								else
								{
									cout << " ";
								}
							}
							else
							{
								cout << " ";
							}
							break;
						default:
							cout << space;
							break;
					}
				}
			
			}

			cout << endl;
		}
	}
}