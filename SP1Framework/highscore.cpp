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
void read(string fileName, playerScore * playerScore)
{
	ifstream openfile(fileName);
	if(fileExists(fileName)==true)
	{
		if(openfile.is_open())
		{
			for(int i = 0 ; !openfile.eof();i++)
			{
				openfile >> playerScore[i].names ;
				openfile >> playerScore[i].score ;
				openfile >> playerScore[i].mapName;
			}
		}
		openfile.close();
	}
}
void displayScores(playerScore * playerScore)
{
	const int PLAYERS = 10;
	//display records
	int highscorePrintSpot = defaultConsoleSize.X/2;
	gotoXY(highscorePrintSpot - 17 , 17);
	cout << "PLAYER NAME";
	gotoXY(highscorePrintSpot, 17);
	cout << " SCORES ";
	gotoXY(highscorePrintSpot + 13 , 17);
	cout << "LEVEL";

		for(int counter = 0 ; counter < PLAYERS ; counter++)
		{
			gotoXY(highscorePrintSpot - 17, 19 + counter);
			cout << playerScore[counter].names ;

			if(playerScore[counter].score > 0)
			{
			gotoXY(highscorePrintSpot, 19 + counter);
			cout<< playerScore[counter].score ;
			}

			gotoXY(highscorePrintSpot + 13, 19 + counter);
			cout << playerScore[counter].mapName ;
		}
}
void highScoreTitle()
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	cls();
	colour(getColourWORD(E_WHITE_COLOR));
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
void sortScore(playerScore * playerScore,int scorePoint,string playerName, string mapName)
{
	for(int i = 0 ; i < 10 ; i++)
	{
		if(playerScore[i].score < scorePoint)
		{
			for(int j = 8 ; j > i ; j--)
			{
				if(j == 8)
				{
					playerScore[9].score = playerScore[8].score;
					playerScore[9].names = playerScore[8].names;
					playerScore[9].mapName = playerScore[8].mapName;
				}
				else
				{
					playerScore[j+1].score = playerScore[j].score;
					playerScore[j+1].names = playerScore[j].names;
					playerScore[j+1].mapName = playerScore[j].mapName;
				}
			}
			playerScore[i].score = scorePoint;
			playerScore[i].names = playerName;
			playerScore[i].mapName = mapName;
			break;
		}
	}
}
void write(string fileName, playerScore * playerScore)	
{
	const int PLAYERS = 10;

	//storing scores into text file
	ofstream openfile (fileName);
	if(openfile.is_open())
	{
		for(int i = 0; i < PLAYERS ; i++)
		{
			openfile << playerScore[i].names <<" ";
			if(playerScore[i].score >= 0)
			openfile<< playerScore[i].score << " ";
			else
				openfile<<" ";
			openfile << playerScore[i].mapName << endl;
		}
	}
	openfile.close();
}
void highScoreBoard(int scorePoint, string mapName)
{
	string scoresDirectory = "Saves/";
	string scoresFileName = scoresDirectory + "scores.cfg";

	highScoreTitle();

	const int PLAYERS = 10;
	playerScore playerScore[PLAYERS];
	for(int i = 0; i < 10 ; i++)
	{
		playerScore[i].names="";
		playerScore[i].score=-1;
		playerScore[i].mapName="";
	}

	read(scoresFileName,playerScore);

	if(scorePoint >= 0)
	{
		string playername;
		gotoXY(40,20);
		cout << "Enter your name(Max. 10 char) : ";
		cin >> playername;
		while(playername.length() > 20)
		{
			gotoXY(40,25);
			cout<<"Your Name has exceeded 10 characters!";
			gotoXY(40,26);
			cout<<"Please enter your name again";
			cin >> playername;
		}

		sortScore(playerScore, scorePoint,playername, mapName);
	}
	cls();
	highScoreTitle();
	displayScores(playerScore);
	
	pressToContinue(40);

	write(scoresFileName,playerScore);
}

void highScoreBoard()
{
	string scoresDirectory = "Saves/";
	string scoresFileName = scoresDirectory + "scores.cfg";

	const int PLAYERS = 10;
	playerScore playerScore[PLAYERS];

	for(int i = 0; i < 10 ; i++)
	{
		playerScore[i].names="";
		playerScore[i].score=-1;
		playerScore[i].mapName="";
	}

	read(scoresFileName,playerScore);

	highScoreTitle();
	displayScores(playerScore);
	
	pressToContinue(30);
}