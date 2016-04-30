#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <vector>
#include <string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
#include "DeckManagement.h"
#include "Interface.h"
#include "GameBoard.h"
#include "PlayerManagement.h"
#include "BotAI.h"
#include "Menu.h"

//Initializes all the game variables
void initGameVariables(std::vector<Player*>* players, std::vector<Card*>* deck, bool* gameEnd, int* direction, bool* skipNext, int* cPlayer, std::string* special);
//Where all variables are found in as well as the main game loop
void startGame();
//Checks if the current player has won, returns true if they have won
bool checkGameState(Player* cPlayer);
//Checks to see if the player wants to play again, returns true if the user typed y
bool askPlayAgain(Player* winner);

#endif