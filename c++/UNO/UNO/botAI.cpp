#include "BotAI.h"

Card* bot::pickCard(Player* bot, std::vector<Card*> botHand, Card* checkCard, int nPCCount)
{
	std::vector<Card*> playableCards;
	//The error of the bot, used to emulate a real human by purposely making errors
	int error;
	//If the bot selects a random card or selects a more reasonal card
	int playRandom;

	//Gets all the cards that the player can play and saves them in a vector
	for (int i = 0; i < botHand.size(); i++) if (checkCanPlayCard(botHand.at(i), *checkCard)) playableCards.push_back(botHand.at(i));

	if (playableCards.size() != 1)
	{
		//Chooses the amount of error depending on the difficulty of the bot
		if (bot->getDifficulty().compare("easy") == 0) error = 60;
		else error = 15;

		//Checks wheter to play a random card or not
		srand(time(NULL));
		playRandom = rand() % 101;

		//Play random card
		if (playRandom >= 100 - error)
		{
			int rCard = rand() % (playableCards.size() - 1);
			return playableCards.at(rCard);
		}
		else
		{
			//Checks if next players card count is less than 3, if it is then it will try and play a special card besides wild cards to not let the player win
			if ((nPCCount <= 3 && bot->getDifficulty() == "easy") || (nPCCount <= 4 && bot->getDifficulty() == "hard"))
			 {
				std::vector<Card*> specialCards;
				//Checks if the player has any special cards besides the wild card, wild draw 4 is also counted
				for (int i = 0; i < playableCards.size(); i++)
				{
					if (playableCards.at(i)->compareValue(Card::vSkip) || playableCards.at(i)->compareValue(Card::vReverse) || playableCards.at(i)->compareValue(Card::vDraw2) || playableCards.at(i)->compareValue(Card::vWildDraw4))
					{
						//Adds the special cards to a new vector
						specialCards.push_back(playableCards.at(i));
					}
				}

				//If there are no special cards, play a number card instead
				if (specialCards.size() != 0)
				{
					//Checks to see if there is only one special card and play that, if not will follow the order
					if (specialCards.size() != 1)
					{
						//Order to play special cards - draw 2, reverse, skip, wild draw 4
						//The order (indexes of Colour::Value)
						int specials[4] = { 12, 11, 10, 14 };

						//Goes through the order and checks if the bot has any of these cards and play it, if not it will continue down the order
						for (int i = 0; i < 4; i++)
						{
							for (int a = 0; a < specialCards.size(); a++)
							{
								//Goes through all the bots special cards and tries and find one in the order, if not goes to the next order index
								if (specialCards.at(a)->compareValue(Card::convertToValue(specials[i]))) return specialCards.at(a);
							}
						}
					}
					else return specialCards.at(0);
				}
				else //Plays any card
				{
					if (bot->getDifficulty() == "easy")
					{
						//Gets a random card
						int rCard = rand() % (playableCards.size() - 1);
						return playableCards.at(rCard);
					}
					else //Hard diff
					{
						//Gets a random card
						int rCard, count = 0;
						do
						{
							//Keeps changing the card until it is not a wild card, saves wild cards for later unless the loop has ran for three times
							count++;
							rCard = rand() % (playableCards.size());

							//Checks if the card value is 0, if it is then it will play it as theres only 4 0 cards
							if (playableCards.at(rCard)->compareValue(Card::v0)) break;
						} while (playableCards.at(rCard)->compareColour(Card::black) && count <= 3);

						return playableCards.at(rCard);
					}
				}
			}
			else //Plays a card
			{
				if (bot->getDifficulty() == "easy")
				{
					//Gets a random card
					int rCard = rand() % (playableCards.size() - 1);
					return playableCards.at(rCard);
				}
				else //Hard diff
				{
					//Gets a random card
					int rCard, count = 0;
					do
					{
						//Keeps changing the card until it is not a wild card, saves wild cards for later unless the loop has ran for three times
						count++;
						rCard = rand() % (playableCards.size());

						//Checks if the card value is 0, if it is then it will play it as theres only 4 0 cards
						if (playableCards.at(rCard)->compareValue(Card::v0)) break;
					} while (playableCards.at(rCard)->compareColour(Card::black) && count <= 3);

					return playableCards.at(rCard);
				}
			}
		}
	}
	else return playableCards.at(0); //Returns the only playable card
}

void bot::checkWildCard(Card* bCard, std::vector<Card*> bHand)
{
	//Checks if the card is a wild card
	if (bCard->compareColour(Card::black))
	{
		//If the wild card is the only card then pick a random colour
		if (bHand.size() != 1)
		{
			//Counts how many of each colour there is
			//0 - red, 1 - yellow, 2 - green, 3 - blue
			int colour[4] = { 0 };

			//Calculates the number of colours there are
			for (int i = 0; i < bHand.size(); i++)
			{
				if (bHand.at(i)->compareColour(Card::red)) colour[0]++;
				else if (bHand.at(i)->compareColour(Card::yellow)) colour[1]++;
				else if (bHand.at(i)->compareColour(Card::green)) colour[2]++;
				else if (bHand.at(i)->compareColour(Card::blue)) colour[3]++;
			}

			//Gets the most occuring colour
			int maxIndex = 0;
			for (int i = 0; i < 4; i++) if (colour[i] > colour[maxIndex]) maxIndex = i;

			//Changes the colour of the wild card to the most occuring colour
			bCard->changeColour(Card::convertToColour(maxIndex));
		}
		else //Gets a random colour
		{
			srand(time(NULL));
			int r = rand() % 3;
			bCard->changeColour(Card::convertToColour(r));
		}
	}
}

