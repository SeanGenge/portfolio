#pragma once
#include "Monster.h"

class Ogre : public Monster
{
public:
	//Constructor
	//statDiffMin is the minimum value from the current stat value
	//statDiffMax is the maximum value from the current stat value
	Ogre(int statDiff = 0, int statDiffAdd = 0);

	//Adds +10% defence every time the monster takes damage
	void setCurrentHealth(double v);

	bool isBoss();
};