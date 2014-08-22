#include "gameStage.h"
#include <iostream>
#include "maps.h"

using std::cout;
using std::cin;
using std::endl;

void mainMenu(gameState &game)
{
	system("color 0F");
	int input = 0;
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
cout<<"        "<<"'########:::::'###:::::'######:::'######:::'##::::'##:'##::: ##:"<<endl;
cout<<"        "<<" ##.... ##:::'## ##:::'##... ##:'##... ##:: ##:::: ##: ###:: ##:"<<endl;
cout<<"        "<<" ##:::: ##::'##:. ##:: ##:::..:: ##:::..::: ##:::: ##: ####: ##:"<<endl;
cout<<"        "<<" ########::'##:::. ##: ##::::::: ##::'####: ##:::: ##: ## ## ##:"<<endl;
cout<<"        "<<" ##.....::: #########: ##::::::: ##::: ##:: ##:::: ##: ##. ####:"<<endl;
cout<<"        "<<" ##:::::::: ##.... ##: ##::: ##: ##::: ##:: ##:::: ##: ##:. ###:"<<endl;
cout<<"        "<<" ##:::::::: ##:::: ##:. ######::. ######:::. #######:: ##::. ##:"<<endl;
cout<<"        "<<"..:::::::::..:::::..:::......::::......:::::.......:::..::::..::"<<endl;

	cout<<endl<<endl<<endl;
	cout <<"              _____________________"<<endl;
	cout <<"              |   Main Menu       |"<<endl;
	cout <<"              |                   |"<<endl;
	cout <<"              |  (1) Load Game    |"<<endl;
	cout <<"              |  (2) Start Game   |"<<endl;
	cout <<"              |  (3) Exit Game    |"<<endl;
    cout <<"              |                   |"<<endl;
	cout <<"              |___________________|"<<endl<<"                 ";
	cin >> input;
	
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