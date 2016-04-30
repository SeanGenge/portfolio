#pragma once
#include <vector>
#include <fstream>
#include "Monster.h"
#include "Player.h"
#include "Human.h"
#include "map.h"

//Saves the game
void saveGame(Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int nM, int nA, Difficulty d, COORD hLoc);
//Loads the game to a previous state
void loadGame(Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int* nM, int* nA, Difficulty* d, COORD* hLoc);
