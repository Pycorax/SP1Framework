#include "gameStage.h"

void mainMenu(gameState &game)
{
	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	char input;
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"                            "<<"'########:::::'###:::::'######:::'######:::'##::::'##:'##::: ##:"<<endl;
	cout<<"                            "<<" ##.... ##:::'## ##:::'##... ##:'##... ##:: ##:::: ##: ###:: ##:"<<endl;
	cout<<"                            "<<" ##:::: ##::'##:. ##:: ##:::..:: ##:::..::: ##:::: ##: ####: ##:"<<endl;
	cout<<"                            "<<" ########::'##:::. ##: ##::::::: ##::'####: ##:::: ##: ## ## ##:"<<endl;
	cout<<"                            "<<" ##.....::: #########: ##::::::: ##::: ##:: ##:::: ##: ##. ####:"<<endl;
	cout<<"                            "<<" ##:::::::: ##.... ##: ##::: ##: ##::: ##:: ##:::: ##: ##:. ###:"<<endl;
	cout<<"                            "<<" ##:::::::: ##:::: ##:. ######::. ######:::. #######:: ##::. ##:"<<endl;
	cout<<"                            "<<"..:::::::::..:::::..:::......::::......:::::.......:::..::::..::"<<endl;

	cout<<endl<<endl<<endl;
	cout <<"                                                    ___________________"<<endl;
	cout <<"                                                   |                   |"<<endl;
	cout <<"                                                   |                   |"<<endl;
	cout <<"                                                   |  (1) Start Game   |"<<endl;
	cout <<"                                                   |  (2) Load Game    |"<<endl;
	cout <<"                                                   |  (3) High Scores  |"<<endl;
	cout <<"                                                   |  (4) Exit Game    |"<<endl;
    cout <<"                                                   |                   |"<<endl;
	cout <<"                                                   |___________________|"<<endl<<"                 ";
	
	input = getchar();

	switch(input)
	{
		case 1:
			game = GAME;
			break;
		case 2:
			game = LOAD_MENU;
			break;
		case 3:
			game = MAIN_MENU;
			break;
		case 4:
			game = QUIT_MENU;
			break;
		default:
			game = MAIN_MENU;
			break;
	}
	
	game = (gameState)input;
}

bool quit(gameState &game)
{
	char input;

	cout << "Are you sure you want to quit? (Y/N)"<<endl;
	cin >> input;

	input = toupper(input);

	if(input == 'Y')
	{
		game = EXIT;
		return true;
	}
	if(input == 'N')
	{
		game = MAIN_MENU;
		return false;
	}
}