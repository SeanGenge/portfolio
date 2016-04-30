#pragma once
#ifndef BOTAI_H
#define BOTAI_H
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "Card.h"
#include "PlayerManagement.h"

namespace bot
{
	//Gets a card following some basic rules
	Card* pickCard(Player* bot, std::vector<Card*> botHand, Card* checkCard, int nPCCount);
	//Checks if the selected card is a wild card, if it is then it will change the colour
	void checkWildCard(Card* bCard, std::vector<Card*> bHand);
}

#endif