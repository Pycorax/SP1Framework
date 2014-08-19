#include "gameStage.h"

void mainMenu()
{

}

void gameScreen(gameState &game)
{


	game = QUIT_MENU;
}

bool quit(gameState &game)
{
	char input;

	cout << "Are you sure you want to quit? (Y/N)";
	cin >> input;

	input = toupper(input);

	if(input == 'Y')
	{
		game = EXIT;
		return true;
	}

	return false;
}