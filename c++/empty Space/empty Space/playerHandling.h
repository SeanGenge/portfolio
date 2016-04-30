#pragma once
#include <vector>
#include "Interface.h"
#include "Human.h"
#include "Artefact.h"
#include"graphics.h"

//Displays the player options when in a battle
void displayPlayerChoices(int x, int y);
//Displays the artefacts of the human
//displayBack will display the back option
//Returns the number of artefacts which are in groups, between 1 and 4
int displayArtefacts(int x, int y, Human* h, bool displayBack = false);
//Gets player input
void getPlayerInput(int x, int y, int min, int max, std::string* input, std::string disp);
//Sorts the artefacts into it's group, eg. all strengh artefacts are grouped as well as the others
std::vector<std::pair<Artefact::type, int>> sortArtefacts(Human* h);
//Checks the number of the index of the artefact the player wants to use
Artefact* useArtefact(int nArtefact, Human* h);
//Changes the players name (asks for input)
void changeName(int x, int y);
//Upgrades the character at the start before the game starts
void upgradeCharacterStartGame();
