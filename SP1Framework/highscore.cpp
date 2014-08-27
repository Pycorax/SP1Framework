#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include "Framework/console.h"
#include "otherHelperFunctions.h"
#include "highscore.h"

extern COORD consoleSize;
extern COORD defaultConsoleSize;

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::getline;
using std::stoi;

//retrieve data from save file
void read(string fileName, playerScore *playerScore)
{
	ifstream openfile(fileName);
	if(openfile.is_open())
	{
		for(int i = 0 ; !openfile.eof();i++)
		{
			openfile >> playerScore[i].names;
			openfile >> playerScore[i].score;
		}
	}
}
void displayScores(playerScore * playerScore)
{
	const int PLAYERS = 10;
	//display records
	int highscorePrintSpot = defaultConsoleSize.X/2 - 8;
	for(int counter = 0 ; counter < PLAYERS ; counter++)
	{
		gotoXY(highscorePrintSpot - 15,17+counter);
		cout << playerScore[counter].names ;
		gotoXY(highscorePrintSpot, 17 + counter);
		cout<< playerScore[counter].score <<endl;

	}

}
void highScoreTitle()
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	cls();
	system("color 0F");
	const size_t HIGH_SCORE_BOARD_TITLE = 8;
	string highscorescreen[HIGH_SCORE_BOARD_TITLE] =
	{
		"'##::::'##:'####::'######:::'##::::'##:::::'######:::'######:::'#######::'########::'########:",
		" ##:::: ##:. ##::'##... ##:: ##:::: ##::::'##... ##:'##... ##:'##.... ##: ##.... ##: ##.....::",
		" ##:::: ##:: ##:: ##:::..::: ##:::: ##:::: ##:::..:: ##:::..:: ##:::: ##: ##:::: ##: ##:::::::",
		" #########:: ##:: ##::'####: #########::::. ######:: ##::::::: ##:::: ##: ########:: ######:::",
		" ##.... ##:: ##:: ##::: ##:: ##.... ##:::::..... ##: ##::::::: ##:::: ##: ##.. ##::: ##...::::",
		" ##:::: ##:: ##:: ##::: ##:: ##:::: ##::::'##::: ##: ##::: ##: ##:::: ##: ##::. ##:: ##:::::::",
		" ##:::: ##:'####:. ######::: ##:::: ##::::. ######::. ######::. #######:: ##:::. ##: ########:",
		"..:::::..::....:::......::::..:::::..::::::......::::......::::.......:::..:::::..::........::"
	};
	int highscorescreenPrintSpot = defaultConsoleSize.X/2 - highscorescreen[0].length()/2;

	for(size_t i = 0; i < HIGH_SCORE_BOARD_TITLE; ++i)
	{
		gotoXY(highscorescreenPrintSpot, 6 + i);
		cout << highscorescreen[i];
	}
}
void sortScore(playerScore * playerScore,int scorePoint,string playerName)
{
	for(int i = 0 ; i < 10 ; i++)
	{
		if(playerScore[i].score < scorePoint)
		{
			for(int j = 9 ; j >= i ; j--)
			{
				if(j == 9)
				{
					playerScore[9].score = playerScore[8].score;
					playerScore[9].names = playerScore[8].names;
				}
				else
				{
					playerScore[j+1].score = playerScore[j].score;
					playerScore[j+1].names = playerScore[j].names;
				}
			}
			playerScore[i].score = scorePoint;
			playerScore[i].names = playerName;
			break;
		}
	}
}
void write(string fileName, playerScore * playerScore)	
{
	const int PLAYERS = 10;

	//storing scores into text file
	ofstream openfile (fileName);
	int i = 0;
	if(openfile.is_open())
	{
		for(int i = 0; i < PLAYERS ; i++)
		{
			openfile << playerScore[i].names <<" "<< playerScore[i].score << endl;
		}
	}
	openfile.close();

}
void highScoreBoard(int scorePoint)
{
	highScoreTitle();
	const int PLAYERS = 10;
	playerScore playerScore[PLAYERS];
	string playername;
	read("scores.txt",playerScore);

	if(scorePoint != -1)
	{
		gotoXY(40,20);
		cout << "Enter your name : ";
		cin >> playername;

		sortScore(playerScore, scorePoint,playername);
	}
	
	cls();
	highScoreTitle();
	displayScores(playerScore);
	gotoXY(40,30);
	cout <<"Press any key to continue...";
	getch();
	write("scores.txt",playerScore);
}