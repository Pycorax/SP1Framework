#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include "Framework/console.h"
#include "otherHelperFunctions.h"
#include "highscore.h"
#include "options.h"

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

void highScoreTitle()
{
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

void highScoreBoard(int scorePoint, string mapName)
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;
	cls();
	colour(getBGColourWORD(E_BLACK_BG_COLOR));

	highScoreTitle();

	vector<Scores> scoreList;
	
	pressToContinue(30);
}

void highScoreBoard()
{
	newSetConsoleSize(defaultConsoleSize);
	consoleSize = defaultConsoleSize;

	colour(getBGColourWORD(E_BLACK_BG_COLOR));
	cls();

	highScoreTitle();

	vector<Scores> scoreList;

	loadScore(scoreList);

	int highScorePrintSpot = consoleSize.X/2 - 4; //4 is the length of "Score"

	colour(getColourWORD(E_WHITE_COLOR));

	gotoXY(highScorePrintSpot - 17, 17);
	cout << "PLAYER NAME";
	gotoXY(highScorePrintSpot, 17);
	cout << "SCORE";
	gotoXY(highScorePrintSpot + 17, 17);
	cout << "LAST LEVEL";

	gotoXY(highScorePrintSpot - 17, 18);
	for (size_t i = 0; i < 44; ++i)
	{
		cout << "*";
	}

	for (size_t i = 0; i < scoreList.size(); ++i)
	{
		gotoXY(highScorePrintSpot - 17, 20 + i * 2);
		cout << scoreList[i].names;
		gotoXY(highScorePrintSpot, 20 + i * 2);
		cout << scoreList[i].score;
		gotoXY(highScorePrintSpot + 20, 20 + i * 2);
		cout << scoreList[i].mapName;
	}

	pressToContinue(30);
}

void loadScore(vector<Scores> &scoreStore)
{
	const unsigned short MAX_HIGH_SCORES = 10;

	string directory = "Saves/";
	string scoreFileName = directory + "scores.cfg";

	ifstream saveFile;
	
	if (fileExists(scoreFileName))
	{
		string readLine;

		saveFile.open(scoreFileName.c_str());

		for(size_t i = 0; i < MAX_HIGH_SCORES; ++i)
		{
			Scores newScore;

			if (saveFile.eof())
			{
				break;
			}

			getline(saveFile, readLine);
			newScore.names = readLine;
			getline(saveFile, readLine);
			newScore.score = atoi(readLine.c_str());
			getline(saveFile, readLine);
			newScore.mapName = readLine;

			scoreStore.push_back(newScore);
		}

		saveFile.close();
	}
}

void saveScore(vector<Scores> &scoreStore)
{
	const unsigned short MAX_HIGH_SCORES = 10;

	string directory = "Saves/";
	string scoreFileName = directory + "scores.cfg";

	ofstream saveFile;

	string readLine;

	saveFile.open(scoreFileName.c_str());

	for(size_t i = 0; i < MAX_HIGH_SCORES; ++i)
	{
		saveFile << scoreStore[i].names << endl;
		saveFile << scoreStore[i].score << endl;
		saveFile << scoreStore[i].mapName << endl;
	}

	saveFile.close();
}