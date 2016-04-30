#include "PlayerManagement.h"

void getNextPlayerTurn(std::vector<Player*> players, int* nextPlayersTurn, int* direction, std::string* special)
{
	if (special->compare("reverse") == 0 && players.size() > 2) //Changes the direction only if theres more than two players
	{
		if (*direction == -1) *direction = 1;
		else if (*direction == 1) *direction = -1;

		*special = "none";
	}

	if (special->compare("skip") == 0 || (players.size() == 2 && special->compare("reverse") == 0)) //Skips the player, if theres two players, skips as well
	{
		if (*direction == 1)
		{
			//Makes sure that the next player is valid, within the player vector
			if (*nextPlayersTurn + 2 == players.size()) *nextPlayersTurn = 0; //Skips the last player
			else if (*nextPlayersTurn + 2 > players.size()) *nextPlayersTurn = 1; //Skips the first player
			else *nextPlayersTurn += 2; //Skips the player after the current player
		}
		else if (*direction == -1)
		{
			//Makes sure that the next player is valid, within the player vector
			if (*nextPlayersTurn - 2 == -1) *nextPlayersTurn = players.size() - 1; //Skips the first player
			else if (*nextPlayersTurn - 2 == -2) *nextPlayersTurn = players.size() - 2; //Skips the last player
			else *nextPlayersTurn -= 2; //Skips the player after the current player
		}

		*special = "none";
	}
	else //Normal action
	{
		if (*direction == 1)
		{
			//Makes sure that the next player is valid, within the player vector
			if (*nextPlayersTurn + 1 == players.size()) *nextPlayersTurn = 0; //Goes to first player
			else *nextPlayersTurn += 1; //Goes to next player
		}
		else if (*direction == -1)
		{
			//Makes sure that the next player is valid, within the player vector
			if (*nextPlayersTurn - 1 == -1) *nextPlayersTurn = players.size() - 1; //Goes to last player
			else *nextPlayersTurn -= 1; //Goes to next player
		}
	}
}

bool checkSpecialDrawCard(Player* cPlayer, std::vector<Card*>* deck, std::string* special)
{
	if (special->compare("draw 2") == 0)
	{
		//Add 1 or 2 cards to the players hand from the deck if the deck is not empty
		for (int i = 1; i <= 2; i++) { if (deck->empty() != true) cPlayer->addCard(deck); }
		*special = "none";
		return true;
	}
	else if (special->compare("wild draw 4") == 0)
	{
		//Add 1, 2, 3 or 4 cards to the players hand from the deck if the deck is not empty
		for (int i = 1; i <= 4; i++) { if (deck->empty() != true) cPlayer->addCard(deck); }
		*special = "none";
		return true;
	}

	return false;
}

void getRandomPlayerTurn(int* cPlayer, int maxSize)
{
	srand(time(NULL));
	*cPlayer = rand() % maxSize;
}

bool checkCanPlayCard(std::vector<Card*> pHand, Card checkCard)
{
	int count = 0;

	for (std::vector<Card*>::iterator i = pHand.begin(); i != pHand.end(); i++)
	{
		//Checks to see if the card matches the checkCard or if it is a wild card
		if ((*i)->compareColour(&checkCard) || (*i)->compareValue(&checkCard) || (*i)->compareColour(Card::black)) count++;
	}

	if (count != 0) return true;
	else return false;
}

bool checkCanPlayCard(Card* pCard, Card checkCard)
{
	//Looks for a match
	if (pCard->compareColour(&checkCard) || pCard->compareValue(&checkCard) || pCard->compareColour(Card::black)) return true;
	else return false;
}

void checkWildCard(Card* pCard)
{
	//Checks if a wild card was played
	if (pCard->compareColour(Card::black))
	{
		;//Displays options
		gotoXY(RIGHTBOARD, INPUTY - 1);
		std::cout << "Choose the colour for the wild card";
		gotoXY(RIGHTBOARD, INPUTY);
		cText("0 - red, ", c_red, 4, 3);
		cText("1 - yellow, ", c_yellow, 4, 6);
		cText("2 - green, ", c_light_green, 4, 5);
		cText("3 - blue", c_light_blue, 4, 4);
		int input;

		//Gets input from the player
		do
		{
			gotoXY(RIGHTBOARD, INPUTY + 1);
			std::cout << "-> ";
			std::cin >> input;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				eraseText(RIGHTBOARD + 3, INPUTY + 1, 41);
			}

			if (input < 0 || input > 3) eraseText(RIGHTBOARD + 3, INPUTY + 1, 41);
		} while (input < 0 || input > 3);

		//Change the colour of the card
		pCard->changeColour(Card::convertToColour(input));
	}
}