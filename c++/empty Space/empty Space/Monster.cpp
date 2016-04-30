#include "Monster.h"

int Monster::_numMonster = 0;
double Monster::_k = 0.20;

Monster::Monster(std::string name, double hp, double att, double def, int speed, int statDiff, int statDiffAdd) : Player(name, hp, att, def, speed)
{
	_numMonster++;

	m_cAction.first = "none";
	m_cAction.second = "";

	//Randomizes the stats
	randomizeStats(statDiff, statDiffAdd);

	m_numAbilities = 0;
}

Monster::~Monster()
{
	_numMonster--;

	m_ability.clear();
}

int Monster::getNumMonsterObjects()
{
	return _numMonster;
}

void Monster::getTurn(Player* defender, double extraDmg)
{
	if (!performSpecialAbility(defender))
	{
		m_cAction.first = "attack";
		m_cAction.second = "";

		attack(defender, extraDmg);
	}

	endTurn();
}

bool Monster::performSpecialAbility(Player* defender)
{
	//Do no special ability by default
	return false;
}

void Monster::endTurn()
{
	//Do nothing
}

int Monster::getVe()
{
	//Gets 1 or -1 for +ve and -ve
	int ve = rand() % 2;
	if (ve == 0) ve = -1;

	return ve;
}

void Monster::randomizeStats(int value, int add)
{
	setMaxHealth(m_mHealth + (rand() % (value + 1) * getVe()) + add);
	m_cHealth = m_mHealth;

	setAttack(m_attack + (rand() % (value + 1) * getVe()) + add);
	setDefence(m_defence + (rand() % (value + 1) * getVe()) + add);
	setSpeed(m_speed + (rand() % (value + 1) * getVe()) + add);
}

void Monster::setRating()
{
	m_rating = ((m_mHealth / 20) + (m_attack * _k) + (m_defence * _k) + (m_speed / 5)) * m_numAbilities;
}

bool Monster::isHuman()
{
	return false;
}