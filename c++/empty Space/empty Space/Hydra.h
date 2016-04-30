#pragma once
#include "Monster.h"

class Hydra : public Monster
{
private:
	//The number of heads of the hydra
	int m_head;

	//Checks if the player has decapitated a head
	bool checkDecapitation();

public:
	//Constructor
	//statDiffMin is the minimum value from the current stat value
	//statDiffMax is the maximum value from the current stat value
	Hydra(int statDiff = 0, int statDiffAdd = 0);

	//Checks if the player has decapitated a head and attacks the number of heads it has
	void attack(Player* defender, double extraDmg);
	//Absorbs 5% dmg
	void setCurrentHealth(double v);
	//Gets the number of heads of the hydra
	inline int getHeadCount() { return m_head; }

	bool isBoss();
};