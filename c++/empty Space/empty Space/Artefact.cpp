#include "Artefact.h"

Artefact::Artefact(bool random, type t)
{
	if (random)
	{
		int r = rand() % 5;
		m_type = changeIntToType(r);
	}
	else m_type = t;

	m_old = 0;

	//Sets info on each type
	switch (m_type)
	{
	case t_shield:
		m_description = "+30% defence for the current turn";
		m_score = 10 + rand() % 5;
		break;
	case t_strength:
		m_description = "+30% attack for the current turn";
		m_score = 10 + rand() % 5;
		break;
	case t_minorHeal:
		m_description = "heals 8 hp";
		m_score = 15 + rand() % 5;
		break;
	case t_majorHeal:
		m_description = "heals 15 hp";
		m_score = 20 + rand() % 5;
		break;
	case t_poison:
		m_description = "-30% defence for the current turn";
		m_score = 10 + rand() % 5;
		break;
	}

	m_name = Artefact::getSType(m_type);
}

std::string Artefact::getSType()
{
	switch (m_type)
	{
	case t_shield: return "shield";
	case t_strength: return "strength";
	case t_minorHeal: return "minor heal";
	case t_majorHeal: return "major heal";
	case t_poison: return "poison";
	}
}

std::string Artefact::getSType(Artefact::type t)
{
	switch (t)
	{
	case t_shield: return "shield";
	case t_strength: return "strength";
	case t_minorHeal: return "minor heal";
	case t_majorHeal: return "major heal";
	case t_poison: return "poison";
	}
}

Artefact::type Artefact::changeIntToType(int v)
{
	switch (v)
	{
	case 0: return t_shield;
	case 1: return t_strength;
	case 2: return t_minorHeal;
	case 3: return t_majorHeal;
	case 4: return t_poison;
	}
}

std::string Artefact::getDescription(Artefact::type t)
{
	Artefact* a = new Artefact(false, t);

	return a->getDescription();
}

void Artefact::performAction(Player* attacker, Player* defender)
{
	//Performs the selected action
	switch (m_type)
	{
	case t_shield:
		m_old = attacker->getDefence();
		attacker->setDefence(m_old + m_old * 0.3);
		m_p = attacker;
		break;
	case t_strength:
		m_old = attacker->getAttack();
		attacker->setAttack(m_old + m_old * 0.3);
		m_p = attacker;
		break;
	case t_minorHeal:
		attacker->setCurrentHealth(attacker->getCurrentHealth() + 8);
		break;
	case t_majorHeal:
		attacker->setCurrentHealth(attacker->getCurrentHealth() + 15);
		break;
	case t_poison:
		//Opponent
		m_old = defender->getDefence();
		defender->setDefence(m_old - m_old * 0.3);
		m_p = defender;
		break;
	}
}

void Artefact::endEffect()
{
	//Reverts stats back to original state
	switch (m_type)
	{
	case t_shield:
		m_p->setDefence(m_old);
		break;
	case t_strength:
		m_p->setAttack(m_old);
		break;
	case t_poison:
		//Opponent
		m_p->setDefence(m_old);
		break;
	}
}