#pragma once
#ifndef DECKMANAGEMENT_H
#define DECKMANAGEMENT_H
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "Card.h"
#include "Player.h"

//Generates and shuffles the deck
void setupDeck(std::vector<Card*>* deck);
//Generates a full deck of UNO cards, clears the deck of cards before generating new cards
void generateDeck(std::vector<Card*>* deck);
//Shuffles the current deck
void shuffleDeck(std::vector<Card*>* deck);
//deletes all the objects within the deck as well as clearing the vector
void newDeck(std::vector<Card*>* deck);
//Gets the first card that will be placed on the table, can only be a number card
void getFirstCard(Card* cCard, std::vector<Card*>* deck);

#endif