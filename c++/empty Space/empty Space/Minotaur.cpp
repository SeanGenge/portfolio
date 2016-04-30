#include "Minotaur.h"

Minotaur::Minotaur(int statDiff, int statDiffAdd) : Monster("Minotaur", 25, 3, 3, 4, statDiff, statDiffAdd)
{
	m_numAbilities = 2;
	//Adds abilities
	m_ability.push_back("20% chance double attack");
	m_ability.push_back("<=10 hp = +3 Att, +4 def");

	//Sets the rating
	setRating();
}

void Minotaur::setCurrentHealth(double v)
{
	double cHp = getCurrentHealth();

	Player::setCurrentHealth(v);

	//rage enabled if less than 10 hp
	if (getCurrentHealth() <= 10 && cHp > 10)
	{
		m_attack += 3;
		m_defence += 4;
		setRating();
	}
}

void Minotaur::attack(Player* defender, double extraDmg)
{
	if (doubleDamage())
	{
		m_cAction.first = "dealt double damage";
		m_cAction.second = "Deals 2x more damage than usual";
		double dmg = calculateDmg(defender, extraDmg) * 2;
		defender->setCurrentHealth(defender->getCurrentHealth() - dmg);
	}
	else Player::attack(defender, extraDmg);
}

bool Minotaur::doubleDamage()
{
	int r = rand() % 100 + 1;

	if (r >= 80) return true;
	else return false;
}

bool Minotaur::isBoss()
{
	return false;
}