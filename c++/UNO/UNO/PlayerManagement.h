#pragma once
#ifndef PLAYERMANAGEMENT_H
#define PLAYERMANAGEMENT_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "Interface.h"
#include "GameBoard.h"
#include "Player.h"
#include "Card.h"

//Gets the next players turn
void getNextPlayerTurn(std::vector<Player*> players, int* nextPlayersTurn, int* direction, std::string* special);
//Gets a random players turn
void getRandomPlayerTurn(int* cPlayer, int maxSize);
//Checks if it is a draw 2 or wild draw 4 cards and adds cards to the players hand if it is
//Changes special to none if special equals to draw 2 or wild draw 4
bool checkSpecialDrawCard(Player* cPlayer, std::vector<Card*>* deck, std::string* special);
//Checks to see if the player's hand of cards match the checkCard as well as having any wild cards
bool checkCanPlayCard(std::vector<Card*> pHand, Card checkCard);
//Checks if the players card matches the colour or the value of the checkCard
bool checkCanPlayCard(Card* pCard, Card checkCard);
//Checks wheter the card is a wild card, if it is then it will ask the player to change the colour of the wild card
void checkWildCard(Card* pCard);

#endif