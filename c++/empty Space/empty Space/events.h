#pragma once
#include <iomanip>
#include <sstream>
#include "Human.h"
#include "Monster.h"
#include "map.h"
#include "status.h"
#include "graphics.h"
#include "playerHandling.h"
#include "difficulty.h"
#include "Hydra.h"

//Checks if there is a monster, artefact or the finish is stepped on
bool checkEventHappened(Map* cSquare);
//Performs the selected action depending on the square that the player is on
void performEvent(Map* cSquare, std::vector<std::string>* status, Human* h, std::vector<Monster*>* m, Map map[mapMaxRow][mapMaxColumn], bool displayAll, Difficulty d, bool* winGame, int* nM, int* nA);
//Adds an artefact to the human
void addArtefact(Human* h, std::vector<std::string>* status);
//Two players can battle
void battle(Player* a, Player* b, Map map[mapMaxRow][mapMaxColumn], bool displayAll, std::vector<std::string>* status, bool* winGame);
//Gets the first monster and removes it from the vector
Monster* getMonster(std::vector<Monster*>* m);
