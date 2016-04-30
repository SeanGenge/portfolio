#include "GameBoard.h"

void displayTitle()
{
	Game* game = Game::getGame();
	game->clearScreen();

	gotoXY(TAB * 3, 0);
	std::cout << "UNO By Sean Genge";
}

void displayBoard(std::vector<Player*> players, Card currentCard, int cPlayer, int direction)
{
	//Draws the player boxes on the left side
	drawPlayerBox(players);

	//Displays the current player (The -> which signals the current players turn)
	displayCurrentPlayer(cPlayer, direction);

	//Displays the current card
	displayCurrentCard(currentCard);

	//Displays the players hand (If the player is a bot, will not display any cards
	displayPlayersHand(players.at(cPlayer), players);
}

void displayCurrentCard(Card cC)
{
	gotoXY(RIGHTBOARD, 2);
	std::cout << "Current Card on table - ";
	displayCardColouredText(cC);
	std::cout << " " << cC.getValue();
}

void displayCardColouredText(Card c)
{
	if (c.getColour() == "red") cText(c.getColour(), c_red);
	else if (c.getColour() == "yellow") cText(c.getColour(), c_yellow);
	else if (c.getColour() == "green") cText(c.getColour(), c_light_green);
	else if (c.getColour() == "blue") cText(c.getColour(), c_light_blue);
}

bool checkAllBots(std::vector<Player*> players)
{
	//Checks all the players and if one is not a bot, return false
	for (int i = 0; i < players.size(); i++) if (players.at(i)->isBot() == false) return false;

	//All the players are bots
	return true;
}

void displayPlayersHand(Player* cPlayer, std::vector<Player*> players)
{
	//Left space for the input
	gotoXY(RIGHTBOARD, getCurrentXY().Y + 7);
	std::cout << cPlayer->getName() << "'s hand";
	gotoXY(RIGHTBOARD, getCurrentXY().Y);

	//Displays the hand of the player only if the player is not a bot or if all the players are bots
	if (!cPlayer->isBot() || checkAllBots(players))
	{
		for (int i = 0; i < cPlayer->getHand().size(); i++)
		{
			gotoXY(RIGHTBOARD, getCurrentXY().Y + 1);

			std::cout << i << " - ";
			//Chooses the colour of the text depending on the colour of the card
			if (cPlayer->getHand().at(i)->getColour() == "red") cText(cPlayer->getHand().at(i)->getColour(), c_red);
			else if (cPlayer->getHand().at(i)->getColour() == "yellow") cText(cPlayer->getHand().at(i)->getColour(), c_yellow);
			else if (cPlayer->getHand().at(i)->getColour() == "green") cText(cPlayer->getHand().at(i)->getColour(), c_light_green);
			else if (cPlayer->getHand().at(i)->getColour() == "blue") cText(cPlayer->getHand().at(i)->getColour(), c_light_blue);

			//Just used to get rid of the extra spacing
			if (cPlayer->getHand().at(i)->compareColour(Card::black)) std::cout << cPlayer->getHand().at(i)->getValue();
			else std::cout << " " << cPlayer->getHand().at(i)->getValue();
		}
	}
	else //Is a bot and there is one human player
	{
		gotoXY(RIGHTBOARD, getCurrentXY().Y + 1);
		std::cout << "Sorry, you cannot view a bots hand!";
	}
}

void drawPlayerBox(std::vector<Player*> players)
{
	std::vector<int> start;

	//Draws the box
	//Maximum is 4 players
	for (int bNum = 0; bNum < 4; bNum++)
	{
		gotoXY(0, 1);
		gotoXY(3, getCurrentXY().Y + bNum * 6);
		start.push_back(bNum * 6 + 2);

		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 28; x++)
			{
				gotoXY(3 + x, getCurrentXY().Y);
				if (y == 0 || y == 4) std::cout << "*";
				else if (x == 0 || x == 27) std::cout << "*";
				else std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	//Display the information within the box
	for (int i = 0; i < 4; i++)
	{
		int begin = start.at(i) + 2;

		if (i < players.size())
		{
			//Displays if the player is a bot or a human and if so the difficulty of the bot
			gotoXY(LEFTBOARD, begin - 2);
			if (players.at(i)->isBot()) std::cout << "\t   Bot - " << players.at(i)->getDifficulty();
			else std::cout << "\t   Human";

			//Displays the name of the player
			gotoXY(LEFTBOARD, begin - 1);
			std::cout << "Name - " << players.at(i)->getName();
			gotoXY(LEFTBOARD, begin);
			std::cout << "# of cards in hand - " << players.at(i)->getHand().size();
		}
		else
		{
			gotoXY(LEFTBOARD, begin - 1);
			std::cout << "\t     Empty";
		}
	}
}

void displayCurrentPlayer(int cPlayer, int direction)
{
	gotoXY(0, cPlayer * 6 + 3);
	std::cout << "->";
	
	switch (direction)
	{
	case -1:
		std::cout << "U";
		break;
	case 1:
		std::cout << "D";
		break;
	}
}