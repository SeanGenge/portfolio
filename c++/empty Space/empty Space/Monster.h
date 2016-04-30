#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include "Player.h"

class Monster : public Player
{
private:
	static int _numMonster;
	static double _k;

	//Gets 1 or -1
	int getVe();

protected:
	//The special abilities
	std::vector<std::string> m_ability;
	//The current action taken
	//First pair is name of action, second pair is description
	//None -> The monster did nothing that round, default value
	//Attack -> The monster just attacked the player dealing damage if they can
	//Ability name -> The monster used an ability
	std::pair<std::string, std::string> m_cAction;

	//The monsters rating
	double m_rating;
	//The number of abilities the monster can perform
	unsigned int m_numAbilities;

	//Changes the stats by +- value and will plud add
	void randomizeStats(int value, int add = 0);

public:
	//Constructor
	Monster(std::string name, double hp, double att, double def, int speed, int statDiff = 0, int statDiffAdd = 0);
	//Descructor
	virtual ~Monster();

	static int getNumMonsterObjects();

	//Gets the rating of the monster
	inline double getRating() { return m_rating; }

	//Gets the vector containing all the abilities
	inline std::vector<std::string> getAbilities() { return m_ability; }
	//Gets the current action taken
	inline std::pair<std::string, std::string> getAction() { return m_cAction; }

	//Gets the monsters turn, follows this specific order
	//Checks if the monster will perform a special ability, if not
	//		Deals damage as normal
	//performs any end turn actions
	void getTurn(Player* defender, double extraDmg);
	//Checks if the monster will perform a special ability
	//Returns true if it has performed a special ability
	virtual bool performSpecialAbility(Player* defender);
	//Always ran at the end of the monsters turn
	virtual void endTurn();

	//Sets the rating of the monster
	void setRating();

	//Returns true if the monster is a boss if not false
	virtual bool isBoss() = 0;
	//Returns false
	bool isHuman();
};