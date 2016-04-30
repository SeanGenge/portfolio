#pragma once
#include <cstdlib>
#include <iostream>
#include "difficulty.h"
#include "Interface.h"

//The different entities you can find in a map
static enum Map
{
	empty = 0,
	human = 1,
	wall = 2,
	monster = 3,
	artefact = 4,
	finish = 5
};

//Maximum map size
const int mapMaxColumn = 20;
const int mapMaxRow = 10;

//Adds monsters, artefacts and random walls to the map as well as the player and exit and the edge walls
void generateMap(Map m[mapMaxRow][mapMaxColumn], int nMonsters, int nArtefacts, COORD* PlayerLoc);
//Draws the map starting at position x and y
//If displayAll = true, draws everything
void drawMap(int x, int y, Map m[mapMaxRow][mapMaxColumn], bool displayAll = false);
//Returns true if the player can go on that square
bool checkMapSquare(Map square);
//Changes an int value to a map value
Map mapIntToMap(int value);