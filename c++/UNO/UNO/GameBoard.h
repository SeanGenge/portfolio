#pragma once
#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include "Interface.h"
#include "Player.h"
#include "Card.h"

//The starting of the right most side of the board
#define RIGHTBOARD 35
//The starting of the left most side of the board
//Note - This value is not where the box starts but where the words start within the boxes, -2 to get where the box's start
#define LEFTBOARD 5
//Where the input starts on the screen, the y coordinate
#define INPUTY 6

//Draws all the board elements
void displayBoard(std::vector<Player*> players, Card currentCard, int cPlayer, int direction);
//Displays the title
void displayTitle();
//Draws the box's where the player info will be displayed
void drawPlayerBox(std::vector<Player*> players);
//Displays an arrow to show whose turn it is
void displayCurrentPlayer(int cPlayer, int direction);
//Displays the current card that is in play
void displayCurrentCard(Card cC);
//Displays only the human players hand
void displayPlayersHand(Player* cPlayer, std::vector<Player*> players);
//Displays the cards colour
void displayCardColouredText(Card c);
//Checks to see if all the players are bots, returns true if all are bots
bool checkAllBots(std::vector<Player*> players);

#endif