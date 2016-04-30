#include "Hydra.h"

Hydra::Hydra(int statDiff, int statDiffAdd) : Monster("Hydra", 50, 8, 7, 10, statDiff, statDiffAdd)
{
	m_numAbilities = 4;
	//Starts with 1 head
	m_head = 1;

	m_name = std::to_string(m_head) + " headed hydra";

	//Adds abilities
	m_ability.push_back("Absorbs 5% dmg/Head");
	m_ability.push_back("+5% attack/Head");
	m_ability.push_back("+5% defence/Head");
	m_ability.push_back("Attacks the number of heads it has");
	m_ability.push_back("10% chance to decapitate a head");

	//Sets the rating
	setRating();
}

bool Hydra::checkDecapitation()
{
	int r = rand() % 100 + 1;

	if (r >= 90)
	{
		//Decapitates and adds 2 more heads -> Just adding one head as you decapitate one
		m_head++;
		//Changes the name to suit the number of heads of the hydra
		m_name = std::to_string(m_head) + " headed hydra";

		return true;
	}
	
	else return false;
}

void Hydra::attack(Player* defender, double extraDmg)
{
	//Attacks the number of heads it has
	//extraDmg is the upperbound of maximum dmg
	double dmg = calculateDmg(defender, extraDmg) * m_head;
	defender->setCurrentHealth(defender->getCurrentHealth() - dmg);

	//If the player decapitates, adds more attack and defence
	if (checkDecapitation())
	{
		//Adds 5% attack and 5% defence for each head
		setAttack(m_attack + m_attack * 0.05);
		setDefence(m_defence + m_defence * 0.05);

		setRating();
	}
}

void Hydra::setCurrentHealth(double v)
{
	double dmg = getCurrentHealth() - v;
	//Absorbs 5% dmg per head
	dmg -= dmg * (0.05 * m_head);

	Player::setCurrentHealth(getCurrentHealth() - dmg);
}

bool Hydra::isBoss()
{
	return true;
}