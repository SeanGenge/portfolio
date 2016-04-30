#pragma once
#include <string>

class Player
{
private:
	static int _numPlayer;

protected:
	//The name of the player
	std::string m_name;

	//The maximum health
	double m_mHealth;
	//The current health
	double m_cHealth;
	//Players attack
	double m_attack;
	//Players defence
	double m_defence;
	//Players speed, who attacks first
	int m_speed;
	//The points of the player
	double m_points;

public:
	//Constructor
	Player(std::string name, double hp, double att, double def, int speed);
	//Destructor
	virtual ~Player();

	//Gets the number of player objects there are
	static int getNumPlayerObjects();

	//Gets the name of the player
	inline std::string getName() { return m_name; }
	//Get max health
	inline double getMaxHealth() { return m_mHealth; }
	//Get current health
	inline double getCurrentHealth() { return m_cHealth; }
	//Get attack
	inline double getAttack() { return m_attack; }
	//Get defence
	inline double getDefence() { return m_defence; }
	//Get speed
	inline int getSpeed() { return m_speed; }
	//Gets the number of points
	inline double getPoints() { return m_points; }

	//Sets the max health only if v is larger than 0
	//Returns false if less than or equal to 0
	bool setMaxHealth(double v);
	//Sets the current health and if it exceeds max health then set the current health to the max health, min is 0
	virtual void setCurrentHealth(double v);
	//Sets attack, min is 0
	void setAttack(double v);
	//Sets defence, min is 0
	void setDefence(double v);
	//Sets speed, min is 0
	void setSpeed(int v);
	//Sets the points
	void setPoints(double v);

	//Gets a random number between 1 and max inclusive
	static int getRandom(int max);
	//Gets a random number between min and max inclusive
	static int getRandom(int min, int max);

	//Gets the calculated attack damage that will be dealt if the two players fought.
	double calculateDmg(Player* defender, double extraDmg = 0);
	//Attacks a player (defender) and deals damage to the defender
	//extraDmg is added to the attack of the attacker
	virtual void attack(Player* defender, double extraDmg = 0);

	//Returns true if the player is alive
	bool isAlive();
	//Returns true if the player is human
	virtual bool isHuman() = 0;
};