#include "menu.h"

void mainMenu(int x, int y, Difficulty* d, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int* nM, int* nA, bool* startGame, bool* lG, COORD* hLoc)
{
	//Gets input from user
	std::string input;
	do
	{
		displayTitle();
		gotoXY(x, y);
		std::cout << "Main menu";
		gotoXY(x, getCurrentXY().Y + 2);
		cText("(1) - Play Game", c_red, 0, 3);
		gotoXY(x, getCurrentXY().Y + 1);
		cText("(2) - Game Options", c_dark_green, 0, 3);
		gotoXY(x, getCurrentXY().Y + 1);
		cText("(3) - Load Game", c_dark_pink, 0, 3);
		gotoXY(x, getCurrentXY().Y + 1);
		cText("(4) - Exit Game", c_dark_yellow, 0, 3);

		int y1 = getCurrentXY().Y + 2;
		getPlayerInput(x, y1, 1, 4, &input, "->");

		if (input.compare("1") == 0)
		{
			*startGame = true;
		}
		else if (input.compare("2") == 0)
		{
			gameOptions(x, y, d, nM, nA);
		}
		else if (input.compare("3") == 0)
		{
			//Tries and reads "save.dat" file, if it does not exist, say there is no saved data
			std::ifstream in("save.dat");

			if (in)
			{
				loadGame(map, m, nM, nA, d, hLoc);
				*startGame = true;
				*lG = true;
			}
			else //No file exists
			{
				displayTitle();
				gotoXY(TAB * 3, getCurrentXY().Y + 2);
				std::cout << "You have no game saved!";
				gotoXY(TAB * 3, getCurrentXY().Y + 2);
				system("PAUSE");
			}

			in.close();
		}
		else if (input.compare("4") == 0)
		{
			Game* g = Game::getGame();
			g->setGameState(false);
			*startGame = false;
		}
	} while (atoi(input.c_str()) == 2);
}

void gameOptions(int x, int y, Difficulty* d, int* nM, int* nA)
{
	//Gets input from user
	std::string input;
	do
	{
		displayTitle();
		gotoXY(x, getCurrentXY().Y + 2);
		cText("(1) - Change name - " + Human::getHumanObject()->getName(), c_red, 0, 3);
		gotoXY(x, getCurrentXY().Y + 1);
		cText("(2) - Change difficulty - " + getDifficulty(*d), c_dark_green, 0, 3);
		gotoXY(x, getCurrentXY().Y + 1);
		cText("(3) - Go back", c_dark_pink, 0, 3);

		int y1 = getCurrentXY().Y + 2;
		getPlayerInput(x, y1, 1, 4, &input, "->");

		if (input.compare("1") == 0)
		{
			changeName(x, y);
		}
		else if (input.compare("2") == 0)
		{
			if (*d == beginner) *d = average;
			else if (*d == average) *d = impossible;
			else if (*d == impossible) *d = beginner;
		}
	} while (atoi(input.c_str()) != 3);
}

void displayInGameMenu(int x, int y, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int nM, int nA, Difficulty d,std::vector<std::string>* status, COORD hLoc)
{
	clearConsoleInputBuffer();
	gotoXY(x, y);
	std::cout << "In game Menu";
	gotoXY(x, getCurrentXY().Y + 2);
	std::cout << "1 - Save Game";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "2 - Exit Game";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "3 - Go Back";

	std::string input;
	getPlayerInput(x, getCurrentXY().Y + 1, 1, 3, &input, "->");

	if (input.compare("1") == 0)
	{
		saveGame(map, m, nM, nA, d, hLoc);
		addStatus("** Game successfully saved **", status);
	}
	else if (input.compare("2") == 0)
	{
		exit(0);
	}
}