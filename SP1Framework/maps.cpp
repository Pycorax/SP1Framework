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

	//Controls Rows
	for (size_t coord_y = 0; coord_y < processedMap.size(); ++coord_y)
	{
		//Controls Columns
		for (size_t coord_x = 0; coord_x < processedMap[coord_y].size(); ++coord_x)
		{	
			COORD tileLocation;
			tileLocation.X = coord_x * TILE_WIDTH;
			tileLocation.Y = coord_y * TILE_HEIGHT + HUD_OFFSET;
			printTile(processedMap[coord_y][coord_x], tileLocation);
		}
	}
}

void printTile(char tile, COORD tileLocation)
{
	const char border = 176;
	const char space = ' ';
	const char obstacle = 176;
	const char pellet = 'o';

	switch(tile)
	{
		case'#':
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXY(tileLocation.X, tileLocation.Y + height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					cout << border;
				}
			}
			break;
		case'O':
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXY(tileLocation.X, tileLocation.Y + height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					cout << obstacle;
				}
			}
			break;
		case '.':
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXY(tileLocation.X, tileLocation.Y + height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					if (height == 1 && width == 1)
					{
						cout << pellet;
					}
					else
					{
						cout << space;
					}
				}
			}
			break;
		default:
			for (size_t height = 0; height < TILE_HEIGHT; ++height)
			{
				gotoXY(tileLocation.X, tileLocation.Y + height);

				for (size_t width = 0; width < TILE_WIDTH; ++ width)
				{
					cout << space;
				}
			}
			break;
	}
}

void printPlayer(COORD charLocation, direction charDirection)
{
	static bool even = true;
	switch(charDirection)
	{
		case UP:
					if(even)
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "(*<";
						even = false;
					}
					else
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "(*=";
						even = true;
					}
				
			break;

		case DOWN:	
					if(even)
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "(*<";
						even = false;
					}
					else
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "(*=";
						even = true;
					}
				 
			break;

		case LEFT:
					if(even)
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << ">*)";
						even = false;
					}
					else
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "=*)";
						even = true;
					}
				 
			break;

		case RIGHT:	
					if(even)
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "(*<";
						even = false;
					}
					else
					{
						gotoXY(charLocation);
						cout << "___";
						gotoXY(charLocation.X, charLocation.Y + 1);
						cout << "(*=";
						even = true;
					}
				 
			break;
	}
}
