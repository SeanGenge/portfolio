#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
private:
	//Returns true if the minotaur will deal double damage
	bool doubleDamage();

public:
	//Constructor
	//statDiffMin is the minimum value from the current stat value
	//statDiffMax is the maximum value from the current stat value
	Minotaur(int statDiff = 0, int statDiffAdd = 0);

	//Decreases the dmg by 15%
	void setCurrentHealth(double v);
	//20% chance to deal double damage
	void attack(Player* defender, double extraDmg = 0);

	bool isBoss();
};