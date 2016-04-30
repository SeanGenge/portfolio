#include "main.h"

int main()
{
	startGame();
	return 0;
}

void initGameVariables(std::vector<Player*>* players, std::vector<Card*>* deck, bool* gameEnd, int* direction, bool* skipNext, int* cPlayer, std::string* special)
{
	newDeck(deck);
	*gameEnd = false;
	*cPlayer = 0;
	*direction = 1;
	*skipNext = false;
	*special = "none";
	
	//Initializes the deck of cards, 108 cards in total
	setupDeck(deck);

	//Deletes all the cards in the players hand and gives them a new hand
	for (int i = 0; i < players->size(); i++) players->at(i)->newHand(7, deck);
}

bool checkGameState(Player* cPlayer)
{
	if (cPlayer->getHand().size() == 0) return true;
	else return false;
}

void startGame()
{
	//Variables
	Game* game = Game::getGame();
	std::vector<Player*> players;
	std::vector<Card*> deck;
	Card* currentCard;
	//The card of the bot if there is a bot
	Card* botCard;
	//used to check if any special action is needed, etc reverse direction or skip next player or draw a number of cards
	std::string special;
	//The current players turn, saves the index
	int cPlayer;
	//-1 is CounterClockwise, 1 is clockwise
	int direction;
	//If it will skip the next player
	bool skipNext;
	bool gameEnd;

	//Compulsory players, need to have minimum of two players
	players.push_back(Player::newPlayer("Player 1", 15, false));
	players.push_back(Player::newPlayer("Player 2", 15, false));

	// --------------------------------------------------------------   GAME LOOP   ------------------------------------------------------------------------
	do //Outer loop, run once per game
	{
		//Display main menu
		mainMenu(&players);

		//Initializes all the game variables
		initGameVariables(&players, &deck, &gameEnd, &direction, &skipNext, &cPlayer, &special);

		//Checks if the player exits the game from the menu
		if (game->run())
		{
			//Used to prevent errors, the new card will be deleted meaning there will not be any extra card
			currentCard = new Card(Card::red, Card::v0);
			botCard = deck.at(0);
			//Picks a card to be placed on the table, can only be a number card
			getFirstCard(currentCard, &deck);
			
			//Adds two cards to the first player if it is a draw 2 card
			if (currentCard->compareValue(Card::vDraw2)) special = "draw 2";

			//Gets a random players turn
			getRandomPlayerTurn(&cPlayer, players.size());

			do //Inner loop, run every players turn
			{
				//Display title
				displayTitle();

				//Get the next players turn, will skip and reverse the direction as well
				getNextPlayerTurn(players, &cPlayer, &direction, &special);

				//Draw board
				displayBoard(players, *currentCard, cPlayer, direction);

				//Check if needing to draw cards, if so, skips their turn, etc draw 2 or draw 4
				if (!checkSpecialDrawCard(players.at(cPlayer), &deck, &special))
				{
					//Check if the player can play a card
					if (checkCanPlayCard(players.at(cPlayer)->getHand(), *currentCard))
					{
						std::string input; //The users input

						//If the current player is human
						if (!players.at(cPlayer)->isBot())
						{
							bool canPlayCard = false; //Used to see if the player can play the currently selected card

							do //Keeps asking for user input until they enter a correct value
							{
								//Get player input
								getInput(RIGHTBOARD, INPUTY, &input);

								//If incorrect input was typed
								if (!checkInput(input, 0, players.at(cPlayer)->getHand().size() - 1)) eraseText(RIGHTBOARD + 3, INPUTY, input.size());

								//Checks if the user can play the currently selected card
								if (atoi(input.c_str()) >= 0 && atoi(input.c_str()) < players.at(cPlayer)->getHand().size())
								{
									if (checkCanPlayCard(players.at(cPlayer)->getHand().at(atoi(input.c_str())), *currentCard)) canPlayCard = true;
									else canPlayCard = false;
								}

								//Makes sure to erase the input if it is within the range but the card cannot be played
								if (canPlayCard == false) eraseText(RIGHTBOARD + 3, INPUTY, input.size());

							} while (!checkInput(input, 0, players.at(cPlayer)->getHand().size() - 1) || !canPlayCard);

							//Sets the special to the value of the card
							special = players.at(cPlayer)->getHand().at(atoi(input.c_str()))->getValue();

							//If the card is a wild card, ask for the colour of the card
							checkWildCard(players.at(cPlayer)->getHand().at(atoi(input.c_str())));
						}
						else //The player is a bot
						{
							int nextPlayer = 0;
							if (direction == 1)
							{
								if (cPlayer + 1 == players.size()) nextPlayer = 0;
								else nextPlayer = cPlayer + 1;
							}
							else
							{
								if (cPlayer - 1 == -1) nextPlayer = players.size() - 1;
								else nextPlayer = cPlayer - 1;;
							}
							//Gets the bots card
							botCard = bot::pickCard(players.at(cPlayer), players.at(cPlayer)->getHand(), currentCard, players.at(nextPlayer)->getHand().size());
							bot::checkWildCard(botCard, players.at(cPlayer)->getHand());

							//Sets the special to the value of the card
							special = botCard->getValue();

							//Displays what the bot has played
							gotoXY(RIGHTBOARD, INPUTY);
							std::cout << "The bot played a ";
							displayCardColouredText(*botCard);
							std::cout << " " << botCard->getValue();
							gotoXY(RIGHTBOARD, INPUTY + 1);
							std::cout << "Please press enter to continue!";
							std::cin.sync();
							std::cin.get();
						}

						//Deletes the current card to free up memory
						delete currentCard;
						if (players.at(cPlayer)->isBot())
						{
							currentCard = botCard;
							players.at(cPlayer)->removeCard(botCard);
						}
						else //A human player
						{
							//Change the current card to the selected players card
							currentCard = players.at(cPlayer)->getCard(atoi(input.c_str()));
							//Removes the card from the players hand
							players.at(cPlayer)->removeCard(atoi(input.c_str()));
						}
					}
					else
					{
						if (deck.empty() != true)
						{
							//Draw a card
							players.at(cPlayer)->addCard(&deck);
							gotoXY(RIGHTBOARD, INPUTY);
							std::cout << players.at(cPlayer)->getName() << " has drawn a card!";
						}
						else //The deck has no cards
						{
							gotoXY(RIGHTBOARD, INPUTY);
							std::cout << "There are no more cards in the deck!";
						}
						gotoXY(RIGHTBOARD, INPUTY + 1);
						std::cout << "Press enter to continue!";
						gotoXY(RIGHTBOARD, INPUTY + 2);
						std::cin.sync();
						std::cin.get();
					}

					//Check if the player wins
					if (checkGameState(players.at(cPlayer))) gameEnd = true;
				}
			} while (!gameEnd);

			//Checks if the player wants to play again
			if (!askPlayAgain(players.at(cPlayer))) game->setGameState(false);
		}

	} while (game->run());
}

bool askPlayAgain(Player* winner)
{
	char input;

	displayTitle();

	gotoXY(TAB * 3, getCurrentXY().Y + 2);
	std::cout << winner->getName() << " wins!";

	gotoXY(TAB * 3, getCurrentXY().Y + 2);
	std::cout << "Would you like to play again? (y - Yes, n - No)" << std::endl;
	int y = getCurrentXY().Y;
	
	do
	{
		gotoXY(TAB * 3, y);
		std::cout << "-> ";
		std::cin >> input;

		if (input != 'y' && input != 'n')
		{
			eraseText(TAB * 3 + 3, y, 1);
		}
	} while (input != 'y' && input != 'n');

	switch (input)
	{
	case 'y':
		return true;
	case 'n':
		return false;
	}
}