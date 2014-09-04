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
	const int AN_IMPOSSIBLY_LOW_SCORE = -10000;
	const int PLAYERS = 10;

	ifstream openfile(fileName);
	if(fileExists(fileName)==true)
	{
		if(openfile.is_open())
		{
			for(int i = 0 ; i < PLAYERS; i++)
			{
				string readLine;
				getline(openfile, readLine);
				playerScore[i].names = readLine;
				getline(openfile, readLine);
				if (readLine.length() > 0)
				{
					playerScore[i].score = atoi(readLine.c_str());
				}
				else
				{
					playerScore[i].score = AN_IMPOSSIBLY_LOW_SCORE;
				}
				
				getline(openfile, readLine);
				playerScore[i].mapName = readLine;
			}
		}
		openfile.close();
	}
}
void displayScores(playerScore * playerScore)
{
	const int PLAYERS = 10;
	const int AN_IMPOSSIBLY_LOW_SCORE = -10000;
	const short SPACE_BETWEEN_HEADERS = 17;

	//display records
	string SPACING = "";
	for(short i = 0; i < SPACE_BETWEEN_HEADERS; ++i)
	{
		SPACING += " ";
	}
	string headerPlayerName = "PLAYER NAME";
	string headerScore = "SCORE";
	string headerLevelPlayed = "LAST LEVEL PLAYED";
	string highScoreHead = headerPlayerName + SPACING + headerScore + SPACING + headerLevelPlayed;

	int highscorePrintSpot = defaultConsoleSize.X/2 - highScoreHead.length()/2;

	gotoXY(highscorePrintSpot, 17);
	cout << highScoreHead;

	for(int counter = 0 ; counter < PLAYERS ; counter++)
	{
		gotoXY(highscorePrintSpot, 19 + counter);
		cout << playerScore[counter].names ;

		if(playerScore[counter].score > AN_IMPOSSIBLY_LOW_SCORE)
		{
			gotoXY(highscorePrintSpot + headerPlayerName.length() + SPACE_BETWEEN_HEADERS, 19 + counter);
			cout<< playerScore[counter].score ;
		}

		gotoXY(highscorePrintSpot + highScoreHead.length() - headerLevelPlayed.length(), 19 + counter);
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
			if(playerScore[i].names != "")
			{
				flushInputBuffer();
				openfile << playerScore[i].names << endl;
				flushInputBuffer();
				openfile<< playerScore[i].score << endl;
				flushInputBuffer();
				openfile << playerScore[i].mapName << endl;
			}
		}
	}
	openfile.close();
}
void highScoreBoard(int scorePoint, string mapName)
{
	const int AN_IMPOSSIBLY_LOW_SCORE = -10000;

	string scoresDirectory = "Saves/";
	string scoresFileName = scoresDirectory + "scores.cfg";

	highScoreTitle();

	const int PLAYERS = 10;
	playerScore playerScore[PLAYERS];
	for(int i = 0; i < 10 ; i++)
	{
		playerScore[i].names = "";
		playerScore[i].score = AN_IMPOSSIBLY_LOW_SCORE;
		playerScore[i].mapName = "";
	}

	read(scoresFileName,playerScore);

	if(scorePoint > AN_IMPOSSIBLY_LOW_SCORE)
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
	const int AN_IMPOSSIBLY_LOW_SCORE = -10000;

	string scoresDirectory = "Saves/";
	string scoresFileName = scoresDirectory + "scores.cfg";

	const int PLAYERS = 10;
	playerScore playerScore[PLAYERS];

	for(int i = 0; i < 10 ; i++)
	{
		playerScore[i].names = "";
		playerScore[i].score = AN_IMPOSSIBLY_LOW_SCORE;
		playerScore[i].mapName = "";
	}

	read(scoresFileName,playerScore);

	highScoreTitle();
	displayScores(playerScore);
	
	pressToContinue(30);
}