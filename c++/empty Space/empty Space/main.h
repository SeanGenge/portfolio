#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <Windows.h>
#undef max

#include "Game.h"
#include "loadSaveGame.h"
#include "events.h"
#include "graphics.h"
#include "Interface.h"
#include "playerHandling.h"
#include "map.h"
#include "difficulty.h"
#include "menu.h"

#include "Artefact.h"
#include "Player.h"
#include "Monster.h"
#include "Human.h"

//Monsters
#include "Ogre.h"
#include "BabyDragon.h"
#include "Minotaur.h"
#include "AncientMummy.h"
#include "Zombie.h"

//Bosses
#include "Hydra.h"

//The number of monster objects
#define NUM_MONSTERS 6

//Where the main game takes place
void mainGame(Game* g);
//Adds monsters in the order of easiest to hardest, boss not included
void setupMonsters(Difficulty d, std::vector<Monster*>* m, int numMonsters);
//Creates a selected monster object of that index
Monster* createMonster(Difficulty d, int index);
//Sets up all the variables default values
void setupVariables(bool* gameStart, bool* displayAll, Human** h, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, Difficulty* diff, int* nMonsters, int* nArtefacts, COORD* hLoc, Map* currentSquare, bool* winGame, bool* loadGame);
//Resets the game variables every time the game is started
void resetGame(bool* gameStart, bool* displayAll, Human** h, std::string hName, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, COORD* hLoc, Map* currentSquare, bool* winGame, bool* loadGame);
//Checks if a key was pressed
bool keyPress(int key);
//Moves the player if they can move
//Returns true if the player was moved
bool movePlayer(Map m[mapMaxRow][mapMaxColumn], COORD* hLoc, int direction, Map* currentSquare);
//Checks if the human is dead or has won the game
bool checkGameFinished(Human* h, bool winGame);
//Asks the player if they want to play the game again
void askPlayAgain();
//Upgrades a player stat as well as the monsters
void upgrade(Human* h, std::vector<Monster*>* m, int stat, Difficulty d);
