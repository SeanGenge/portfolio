#include "BabyDragon.h"

BabyDragon::BabyDragon(int statDiff, int statDiffAdd) : Monster("Baby Dragon", 25, 5, 5, 5, statDiff, statDiffAdd)
{

	m_numAbilities = 2;
	//Adds abilities
	m_ability.push_back("Fire breath - -15% to opponents defence");
	m_ability.push_back("Absorbs 15% damage");

	//Sets the rating
	setRating();
}

void BabyDragon::setCurrentHealth(double v)
{
	double dmg = m_cHealth - v;
	dmg -= dmg * 0.15;

	double finalHealth = m_cHealth - dmg;

	Player::setCurrentHealth(finalHealth);
}

void BabyDragon::fireBreath(Player* defender)
{
	double decreaseDefence = defender->getDefence() * 0.15;
	defender->setDefence(defender->getDefence() - decreaseDefence);
}

bool BabyDragon::performSpecialAbility(Player* defender)
{
	int r = rand() % 100 + 1;

	//If the players defence is too great, use firebreath
	//If not if the percentage is high enough, perform fireBreath
	if (defender->getDefence() > this->getAttack() + 6)
	{
		fireBreath(defender);
		m_cAction.first = "used fire Breath";
		m_cAction.second = "-15% to opponents defence";
		return true;
	}
	else if (r >= 85)
	{
		fireBreath(defender);
		m_cAction.first = "used fire breath";
		m_cAction.second = "-15% to opponents defence";
		return true;
	}

	return false;
}

bool BabyDragon::isBoss()
{
	return false;
}