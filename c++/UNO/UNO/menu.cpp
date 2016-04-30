#include "Menu.h"

void mainMenu(std::vector<Player*>* players)
{
	bool startGame = false;

	do
	{
		displayTitle();

		std::string input;

		//Displays the menu options
		gotoXY(TAB * 3, getCurrentXY().Y + 2);
		std::cout << "Main Menu";
		gotoXY(TAB * 3, getCurrentXY().Y + 2);
		cText("1 - Play UNO", c_red, 0, 1);
		gotoXY(TAB * 3, getCurrentXY().Y + 1);
		cText("2 - Game options", c_light_blue, 0, 1);
		gotoXY(TAB * 3, getCurrentXY().Y + 1);
		cText("3 - How to play UNO", c_yellow, 0, 1);
		gotoXY(TAB * 3, getCurrentXY().Y + 1);
		cText("4 - Exit Game", c_light_green, 0, 1);

		gotoXY(0, getCurrentXY().Y + 2);
		int y = getCurrentXY().Y;
		do
		{
			//Gets the input from the user
			getInput(TAB * 3, y, &input);

			//Clears the text if wrong input was typed
			if (!checkInput(input, 1, 4)) eraseText(TAB * 3 + 3, y, input.length());
		} while (!checkInput(input, 1, 4));

		//Performs the selected action
		switch (atoi(input.c_str()))
		{
		case 1: //Play UNO
			//Gets out of the loop
			startGame = true;
			break;
		case 2: //Game options
			gameOptions(players);
			break;
		case 3: //Help
			displayHelp();
			break;
		case 4: //Exits game
			Game* game = Game::getGame();
			game->setGameState(false);
			//Used to get out of loop which then the game will end
			startGame = true;
			break;
		}
	} while (!startGame);
}

void gameOptions(std::vector<Player*>* players)
{
	std::string input;
	bool goBack = false;

	do
	{
		displayTitle();

		gotoXY(TAB * 3, getCurrentXY().Y + 2);
		std::cout << "Game Options!";

		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		cText("1 - Change player names", c_red, 0, 1);
		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		cText("2 - Change number of players", c_yellow, 0, 1);
		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		cText("3 - Change player details (eg. add bots, change bot difficulty)", c_light_teal, 0, 1);
		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		cText("4 - Go back", c_light_blue, 0, 1);

		gotoXY(0, getCurrentXY().Y + 2);
		int y = getCurrentXY().Y;
		do
		{
			//Gets the input from the user
			getInput(TAB * 3, y, &input);

			//Clears the text if wrong input was typed
			if (!checkInput(input, 1, 4)) eraseText(TAB * 3 + 3, y, input.length());
		} while (!checkInput(input, 1, 4));

		//Performs the selected action
		switch (atoi(input.c_str()))
		{
		case 1: //Change player names
			changePlayerNames(players);
			break;
		case 2: //Change number of players
			changeNumberPlayers(players);
			break;
		case 3: //Change player details
			changePlayerDetails(players);
			break;
		case 4: //Go back to menu
			goBack = true;
			break;
		}
	} while (!goBack);
	
}

void changePlayerDetails(std::vector<Player*>* players)
{
	displayTitle();
	std::string input;

	gotoXY(TAB * 2, getCurrentXY().Y + 2);
	std::cout << "Change player details";
	gotoXY(TAB * 2, getCurrentXY().Y + 2);
	std::cout << "Please choose a player you would like to change";
	gotoXY(TAB * 2, getCurrentXY().Y + 1);
	std::cout << "-1 to go back";

	//Displays the players index and their name
	for (int i = 0; i < players->size(); i++)
	{
		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		cText(std::to_string(i) + " - " + players->at(i)->getName(), c_red, 0, 1);
	}

	int y = getCurrentXY().Y + 2;
	//Gets the player who they want to change
	do
	{
		getInput(TAB * 2, y, &input);

		if (!checkInput(input, -1, players->size() - 1)) eraseText(TAB * 2 + 3, y, input.length());
	} while (!checkInput(input, -1, players->size() - 1));

	int pIndex = atoi(input.c_str());

	//Displays the menu options for the selected player
	if (input.compare("-1") != 0)
	{
		bool goBack = false;

		do
		{
			displayTitle();

			//Displays the specific player options
			gotoXY(TAB * 2, getCurrentXY().Y + 2);
			std::cout << "Changing options for " << players->at(pIndex)->getName();
			gotoXY(TAB * 2, getCurrentXY().Y + 2);
			if (players->at(pIndex)->isBot()) cText("1 - Disable bot", c_red, 0, 1);
			else cText("1 - Enable bot", c_red, 0, 1);
			if (players->at(pIndex)->isBot())
			{
				gotoXY(TAB * 2, getCurrentXY().Y + 1);
				cText("2 - Bot difficulty - " + players->at(pIndex)->getDifficulty(), c_dark_green, 0, 1);
			}
			gotoXY(TAB * 2, getCurrentXY().Y + 1);
			cText("3 - Go back", c_dark_pink, 0, 1);

			int y = getCurrentXY().Y + 2;
			//Gets the menu option
			do
			{
				getInput(TAB * 2, y, &input);

				if (!checkInput(input, 1, 3)) eraseText(TAB * 2 + 3, y, input.length());
			} while (!checkInput(input, 1, 3));

			switch (atoi(input.c_str()))
			{
			case 1: //Enable/Disable bot
				players->at(pIndex)->toggleBot(!players->at(pIndex)->isBot());
				break;
			case 2: //Change bot difficulty
				if (players->at(pIndex)->getDifficulty() == "easy") players->at(pIndex)->changeDifficulty("hard");
				else if (players->at(pIndex)->getDifficulty() == "hard")players->at(pIndex)->changeDifficulty("easy");
				break;
			case 3: //Go back to game options
				goBack = true;
				break;
			}
		} while (!goBack);
	}
}

void changeNumberPlayers(std::vector<Player*>* players)
{
	displayTitle();
	std::string input;

	gotoXY(TAB * 2, getCurrentXY().Y + 2);
	std::cout << "How many players would you like (2 - 4 players)?";
	gotoXY(TAB * 2, getCurrentXY().Y + 1);
	std::cout << "-1 to go back";

	int y = getCurrentXY().Y + 1;
	do
	{
		getInput(TAB * 2, y, &input);

		if (!checkInput(input, 2, 4) && atoi(input.c_str()) != -1) eraseText(TAB * 2 + 3, y, input.length());
	} while (!checkInput(input, 2, 4) && atoi(input.c_str()) != -1);

	int maxPlayers = atoi(input.c_str());
	if (maxPlayers != -1)
	{
		//Add or decrease players
		if (maxPlayers > players->size())
		{
			//adds players
			for (int i = players->size(); i < maxPlayers; i++) players->push_back(Player::newPlayer("Player " + std::to_string(i + 1), 15, false));
		}
		else if (maxPlayers < players->size())
		{
			//Erases players
			for (int i = players->size() - 1; i >= maxPlayers; i--)
			{
				delete players->at(i);
				players->erase(players->begin() + i);
			}
		}
	}
}

void changePlayerNames(std::vector<Player*>* players)
{
	displayTitle();
	std::string input;

	gotoXY(TAB * 3, getCurrentXY().Y + 2);
	std::cout << "Change player names!";

	gotoXY(TAB * 2, getCurrentXY().Y + 2);
	std::cout << "Which player's name would you like to change (-1 to go back)?";

	//Displays the players index and their name
	for (int i = 0; i < players->size(); i++)
	{
		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		cText(std::to_string(i) + " - " + players->at(i)->getName(), c_red, 0, 1);
	}

	int y = getCurrentXY().Y + 2;
	//Gets the player who they want to change
	do
	{
		getInput(TAB * 2, y, &input);

		if (!checkInput(input, -1, players->size() - 1)) eraseText(TAB * 2 + 3, y, input.length());
	} while (!checkInput(input, -1, players->size() - 1));
	
	int pIndex = -1;

	switch (atoi(input.c_str()))
	{
	case -1: //Goes back
		//Do nothing
		break;
	default: //If the player selected an index of a player
		pIndex = atoi(input.c_str());
		break;
	}

	//Changes the players name
	if (pIndex != -1)
	{
		gotoXY(TAB * 2, getCurrentXY().Y + 2);
		std::cout << "Changing " << players->at(pIndex)->getName() << " name (-1 to go back)";

		gotoXY(TAB * 2, getCurrentXY().Y + 1);
		std::cout << "Please enter a new name";
		//Asks the user for a new name
		int y2 = getCurrentXY().Y + 1;
		do
		{
			getInput(TAB * 2, y2, &input);

			if (input.at(0) == ' ' && input.length() > 15) eraseText(TAB * 2 + 3, y2, input.length());
		} while (input.at(0) == ' ' && input.length() > 15);

		//Changes the name
		if (input.compare("-1") != 0) players->at(pIndex)->changeName(input, 15);
	}
}

void displayHelp()
{
	displayTitle();

	gotoXY(TAB * 3, getCurrentXY().Y + 2);
	std::cout << "How to play UNO";

	//Displays the basics of the game and how to play
	gotoXY(TAB, getCurrentXY().Y + 2);
	std::cout << "Objective - To be the first to get rid of all the cards in your hand.";
	gotoXY(TAB, getCurrentXY().Y + 2);
	std::cout << "Each player starts with 7 cards in their hand, you can only play a card";
	gotoXY(TAB, getCurrentXY().Y + 1);
	std::cout << "if the card you want to play matches the colour or the value of the";
	gotoXY(TAB, getCurrentXY().Y + 1);
	std::cout << "card on the table. If the first card is draw 2, you must draw 2 cards!";

	//tells the player about all the special cards that you can get in the game
	gotoXY(TAB * 3, getCurrentXY().Y + 2);
	std::cout << "Special cards";
	gotoXY(TAB, getCurrentXY().Y + 1);
	cText("Reverse - Reverses the direction of who would go next. If there are", c_red, 0, 7);
	gotoXY(TAB, getCurrentXY().Y + 1);
	std::cout << "\t  two players, it acts exactly like a skip card.";
	gotoXY(TAB, getCurrentXY().Y + 1);
	cText("Skip - Skips the next players turn.", c_light_green, 0, 4);
	gotoXY(TAB, getCurrentXY().Y + 1);
	cText("Draw 2 - The next player's turn has to draw two extra cards and their", c_dark_teal, 0, 6);
	gotoXY(TAB, getCurrentXY().Y + 1);
	std::cout << "\t turn is skipped.";
	gotoXY(TAB, getCurrentXY().Y + 1);
	cText("Wild - You can change the colour of the card to be and valid colour.", c_yellow, 0, 4);
	gotoXY(TAB, getCurrentXY().Y + 1);
	cText("Wild draw 4 - The same as a wild card except the next player draws 4", c_dark_blue, 0, 11);
	gotoXY(TAB, getCurrentXY().Y + 1);
	std::cout << "\t      cards and their turn is skipped.";

	gotoXY(TAB * 2, getCurrentXY().Y + 2);
	std::cout << "Press enter to go back to the menu!";
	std::cin.get();
}