#include "deckManagement.h"

void setupDeck(std::vector<Card*>* deck)
{
	generateDeck(deck);
	shuffleDeck(deck);
}

void generateDeck(std::vector<Card*>* deck)
{
	//Generates all the cards for the UNO game
	//First loop loops through the colours, 0 - 4
	//Second loop loops through the values, 1 - 12
	for (int c = 0; c < 4; c++)
	{
		for (int v = 1; v <= 12; v++)
		{
			//Creates two of each card for each colour
			deck->push_back(new Card(Card::convertToColour(c), Card::convertToValue(v)));
			deck->push_back(new Card(Card::convertToColour(c), Card::convertToValue(v)));
		}
		//Adds only four zero card
		deck->push_back(new Card(Card::convertToColour(c), Card::convertToValue(0)));
		//Adds only four wild cards
		deck->push_back(new Card(Card::convertToColour(4), Card::convertToValue(13)));
		//Adds only four wild draw 4 cards
		deck->push_back(new Card(Card::convertToColour(4), Card::convertToValue(14)));
	}
}

void shuffleDeck(std::vector<Card*>* deck)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	//Shuffles the elements
	shuffle(deck->begin(), deck->end(), std::default_random_engine(seed));
}

void newDeck(std::vector<Card*>* deck)
{
	if (deck->empty() != true)
	{
		for (std::vector<Card*>::iterator i = deck->begin(); i != deck->end(); i++) delete *i;
		deck->clear();
	}
}

void getFirstCard(Card* cCard, std::vector<Card*>* deck)
{

	for (int c = 0; c < deck->size(); c++)
	{
		//Checks to see if the card is a special card, will not play it
		if (!deck->at(c)->compareColour(Card::black) && !deck->at(c)->compareValue(Card::vSkip) && !deck->at(c)->compareValue(Card::vReverse))
		{
			*cCard = *deck->at(c);
			deck->erase(deck->begin() + c);
			break;
		}
	}
}