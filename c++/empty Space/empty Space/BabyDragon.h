#pragma once
#include "Monster.h"
#include "Player.h"

class BabyDragon : public Monster
{
private:
	//Takes in a player and decreases their defence by 15%
	void fireBreath(Player* defender);

public:
	//Constructor
	//statDiffMin is the minimum value from the current stat value
	//statDiffMax is the maximum value from the current stat value
	BabyDragon(int statDiff = 0, int statDiffAdd = 0);

	//Decreases the dmg by 15%
	void setCurrentHealth(double v);
	//if the players defence is too high, use fireBreath if not 15% chance of doing fireBreath
	bool performSpecialAbility(Player* defender);

	bool isBoss();
};