#pragma once
#include "Monster.h"

class AncientMummy : public Monster
{
public:
	//Constructor
	//statDiffMin is the minimum value from the current stat value
	//statDiffMax is the maximum value from the current stat value
	AncientMummy(int statDiff = 0, int statDiffAdd = 0);

	//Regenerates 5% of it's maximum health
	void endTurn();

	bool isBoss();
};