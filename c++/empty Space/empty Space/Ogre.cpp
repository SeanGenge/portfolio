#include "Ogre.h"

Ogre::Ogre(int statDiff, int statDiffAdd) : Monster("Ogre", 20, 5, 1, 2, statDiff, statDiffAdd)
{
	m_numAbilities = 1;

	//Adds abilities
	m_ability.push_back("Every dmg taken = +10% defence");

	//Sets the rating
	setRating();
}

bool Ogre::isBoss()
{
	return false;
}

void Ogre::setCurrentHealth(double v)
{
	double oldHealth = getCurrentHealth();
	Player::setCurrentHealth(v);

	//Damage was dealt
	if (v - oldHealth < 0)
	{
		m_defence += m_defence * 0.1;
		setRating();
	}
}