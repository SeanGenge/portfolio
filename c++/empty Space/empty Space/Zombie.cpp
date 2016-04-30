#include "Zombie.h"

Zombie::Zombie(int statDiff, int statDiffAdd) : Monster("Zombie", 15, 3, 2, 1, statDiff, statDiffAdd)
{
	m_numAbilities = 1;

	//Adds abilities
	m_ability.push_back("30% chance they wont stay dead");

	//Sets the rating
	setRating();
}

void Zombie::setCurrentHealth(double v)
{
	Player::setCurrentHealth(v);

	if (!isAlive())
	{
		int r = rand() % 100 + 1;

		//The zombie is brought back from the dead
		if (r >= 70)
		{
			m_cAction.first = "came back to life";
			m_cAction.second = "the zombie did not die!";
			setCurrentHealth(m_mHealth);
		}
	}
}

bool Zombie::isBoss()
{
	return false;
}