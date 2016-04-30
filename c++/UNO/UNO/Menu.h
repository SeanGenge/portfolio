#pragma once
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <vector>
#include "Interface.h"
#include "GameBoard.h"
#include "Game.h"
#include "Player.h"

void mainMenu(std::vector<Player*>* players);
void displayHelp();
void gameOptions(std::vector<Player*>* players);
void changePlayerNames(std::vector<Player*>* players);
void changeNumberPlayers(std::vector<Player*>* players);
void changePlayerDetails(std::vector<Player*>* players);

#endif