#pragma once
#include <string>
#include <cstdlib>
#include "Player.h"

class Artefact
{
public:
	static enum type
	{
		t_shield = 0,
		t_strength,
		t_minorHeal,
		t_majorHeal,
		t_poison = 4
	};

	//Constructor
	//Default value for t is shield
	//Use random if you want to get a random type if not set to false and manually set a type
	Artefact(bool random, type t = t_shield);

	//Gets the type of the artefact
	inline type getType() { return m_type; }
	inline std::string getDescription() { return m_description; }
	inline int getScore() { return m_score; }
	static std::string getDescription(type t);
	//Gets the type of the artefact as a string
	std::string getSType();
	//Gets the type of a selected type as a string
	static std::string Artefact::getSType(Artefact::type t);
	//Changes an integer value to type
	//Default value is 0
	static type changeIntToType(int v);

	//Performs the selected action
	//Other can be the opponent fighting or the player calling the artefact
	void performAction(Player* attacker, Player* defender);
	//Revert stats back to normal
	void endEffect();

private:
	//The name of the artefact
	std::string m_name;
	//The description of the artefact
	std::string m_description;
	//The score of the artefact if you do not use it
	int m_score;
	//Keeps track of the old value so once the cooldown reaches 0, the effects will revert back
	double m_old;
	//Keeps track of the person it has affected
	Player* m_p;
	//The effects of the type
	type m_type;

};