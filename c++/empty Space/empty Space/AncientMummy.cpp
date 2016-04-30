#include "AncientMummy.h"

AncientMummy::AncientMummy(int statDiff, int statDiffAdd) : Monster("Ancient mummy", 20, 5, 4, 8, statDiff, statDiffAdd)
{
	m_numAbilities = 1;

	//Adds abilities
	m_ability.push_back("Regenerates 5% of it's maximum health after it's turn");

	//Sets the rating
	setRating();
}

void AncientMummy::endTurn()
{
	//Regenerates
	setCurrentHealth(m_cHealth + m_mHealth * 0.05);
}

bool AncientMummy::isBoss()
{
	return false;
}