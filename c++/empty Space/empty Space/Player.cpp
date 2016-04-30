#include "Player.h"

int Player::_numPlayer = 0;

Player::Player(std::string name, double hp, double att, double def, int speed)
{
	_numPlayer++;

	m_name = name;

	//Sets the stats
	//If max health is less than 0, sets the max health to 1
	if (!setMaxHealth(hp)) setMaxHealth(1);
	//Sets the current health
	setCurrentHealth(hp);
	//Sets the attack
	setAttack(att);
	//Sets the defence
	setDefence(def);
	//Sets the speed
	setSpeed(speed);
	//Sets the points
	m_points = 0;
}

Player::~Player()
{
	_numPlayer--;
}

int Player::getNumPlayerObjects()
{
	return _numPlayer;
}

bool Player::setMaxHealth(double v)
{
	if (v > 0)
	{
		if (m_cHealth > v) m_cHealth = v;
		m_mHealth = v;

		return true;
	}
	else return false;
}

void Player::setCurrentHealth(double v)
{
	if (v >= 0)
	{
		if (v >= m_mHealth) m_cHealth = m_mHealth;
		else m_cHealth = v;
	}
	else m_cHealth = 0;
}

void Player::setAttack(double v)
{
	if (v >= 0) m_attack = v;
	else m_attack = 0;
}

void Player::setDefence(double v)
{
	if (v >= 0) m_defence = v;
	else m_defence = 0;
}

void Player::setSpeed(int v)
{
	if (v >= 0) m_speed = v;
	else m_speed = 0;
}

void Player::setPoints(double v)
{
	if (v >= 0) m_points = v;
	else m_points = 0;
}

int Player::getRandom(int max)
{
	return rand() % max + 1;
}

int getRandom(int min, int max)
{
	return rand() % (max - min) + min;
}

bool Player::isAlive()
{
	if (m_cHealth == 0) return false;
	else return true;
}

double Player::calculateDmg(Player* defender, double extraDmg)
{
	//Damage Formula -> (attacker's attack + extraDmg) - defender's defence
	double dmg = (this->getAttack() + extraDmg) - defender->getDefence();
	if (dmg <= 0) dmg = 0;

	return dmg;
}

void Player::attack(Player* defender, double extraDmg)
{
	double dmg = this->calculateDmg(defender, extraDmg);

	defender->setCurrentHealth(defender->getCurrentHealth() - dmg);
}