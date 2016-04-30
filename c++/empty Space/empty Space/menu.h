#pragma once
#include <fstream>
#include "difficulty.h"
#include "Game.h"
#include "Interface.h"
#include "graphics.h"
#include "playerHandling.h"
#include "loadSaveGame.h"
#include "status.h"

//The main menu of the game
void mainMenu(int x, int y, Difficulty* d, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int* nM, int* nA, bool* startGame, bool* lG, COORD* hLoc);
//The game options, to change the players name and difficulty setting
void gameOptions(int x, int y, Difficulty* d, int* nM, int* nA);
void displayInGameMenu(int x, int y, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int nM, int nA, Difficulty d, std::vector<std::string>* status, COORD hLoc);
