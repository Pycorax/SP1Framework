#include "gameStage.h"

void mainMenu()
{

}

void gameScreen(gameState &game)
{
	vector<vector<char>> processedMap;

	processMap("testing.map", processedMap);

	renderMap(processedMap);

	game = QUIT_MENU;
}

void quit(gameState &game)
{
	char input;

	cout << "Are you sure you want to quit? (Y/N)";
	cin >> input;

	input = toupper(input);

	if(input == 'Y')
	{
		game = EXIT;
	}
}