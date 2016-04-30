#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include "Interface.h"
#include "map.h"
#include "Player.h"
#include "Human.h"
#include "Monster.h"

//The starting left side of the board
#define LEFT_BOARD 2
//The starting right side of the board
#define RIGHT_BOARD 43

//Displays the title, always clears screen before the title is displayed
void displayTitle();
//Draws the status box which will display information
void drawStatusBoard(int x, int y, int sizeX, int sizeY, std::string disp, Colour dispC, std::vector<std::string> description, Colour descC, bool dispTitle = false, std::string title = "", Colour titleC = c_white);
//Draws the main items to the screen, the board and the status board
void drawMain(Map map[mapMaxRow][mapMaxColumn], bool displayAll, std::vector<std::string> status);
//Draws the stats of each player
void drawBattle(Player* a, Player* b, int startY, Map map[mapMaxRow][mapMaxColumn], bool displayAll, std::vector<std::string>* status);
//Displays all the monster abilities
void displayMonsterAbilities(int x, int y, Monster* m);
//Displays the player options when the player is allowed to move in the map
void playerOptions(int x, int y);
//Displays the human stats
void displayHumanStats(int x, int y, Human* h);
//Displays the upgrade options
void displayUpgradeOptions(int x, int y, Human* h, bool displayBack);
//Displays how many monsters and artefacts there are left on the board
void drawGameStat(int x, int y, int nM, int nA);
