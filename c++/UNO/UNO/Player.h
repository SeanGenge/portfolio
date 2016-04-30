#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Card.h"

class Player
{
protected:
	//Constructor
	Player(std::string name, bool isBot, std::string botDifficulty);

	//The total number of player objects created
	static int _totalPlayers;
	
	//The name of the player
	std::string m_name;
	//The hand of the player (Hand of cards)
	std::vector<Card*> m_hand;
	//If the current player is a bot
	bool m_isBot;
	//Bot difficulty -> none, easy and hard
	std::string m_botDifficulty;

public:
	//Destructor
	virtual ~Player();

	//Creates the player only if certain conditions are met
	//Bot difficulty -> none, easy and hard
	static Player* newPlayer(std::string name, int maxLength, bool isBot, std::string botDifficulty = "none");

	//Gets the number of player objects
	static int getTotalPlayerObjects();

	//Changes the name of the player, returns true if successful
	bool changeName(std::string newName, int maxLength);
	//Gets the name of the player
	std::string getName();

	//Returns wheter the current player is a bot, default is human
	bool isBot();
	//Gets the bots difficulty
	std::string getDifficulty();
	void toggleBot(bool activate);
	void changeDifficulty(std::string newDifficulty);

	//Gets the players hand
	std::vector<Card*> getHand();
	//Returns the actual address of the card at the selected index in the hand
	Card* getCard(int index);
	//Creates a new hand for the player and discards the old hand, returns true if successful
	bool newHand(int maxHand, std::vector<Card*>* deck);

	//Removes a card at the specified index, returns true if successful
	bool removeCard(int index);
	//Removes card of the specified colour and value (first instance of the card), returns true if successful
	bool removeCard(Card::value v, Card::colour c);
	//Removes a card which matches the selected card perfectly, removes the first instance of the card
	bool removeCard(Card* card);

	//Adds a card to the users hand
	void addCard(Card* c);
	//Adds the first element of the card from a deck to the users hand and removes that card from the deck, returns true if successful
	bool addCard(std::vector<Card*>* deck);
	//Adds a specified number of cards to the users hand from a deck, returns true if successful
	bool addCard(std::vector<Card*>* deck, int numCards);
};

#endif