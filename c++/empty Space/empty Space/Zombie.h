#pragma once
#include "Monster.h"

class Zombie : public Monster
{
private:
	//Checks if the player needs to verse the zombie again
	//Returns true if the zombie comes alive again
	bool notDead();
public:
	//Constructor
	//statDiffMin is the minimum value from the current stat value
	//statDiffMax is the maximum value from the current stat value
	Zombie(int statDiff = 0, int statDiffAdd = 0);

	void setCurrentHealth(double v);

	bool isBoss();
};