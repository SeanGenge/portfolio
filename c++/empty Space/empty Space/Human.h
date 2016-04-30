#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Artefact.h"

class Human : public Player
{
private:
	static Human* _human;

	//The number of artefacts the human has
	//the second pair = 1 if in use, 0 if not in use
	std::vector<Artefact*> m_artefact;
	//How many souls the human player has gotten
	int m_souls;

	//Constructor
	Human(std::string name, double hp, double att, double def, int speed);

public:
	//creates a human if it does not exist if not get the only human object allowed
	static Human* getHumanObject(std::string name = "human", double hp = 0, double att = 0, double def = 0, int speed = 0);
	//Deletes the human object
	//Does not clear any objects within the object
	void deleteHuman();

	void setName(std::string newName);

	//Adds v to the number of souls already collected
	//If the number goes below 0, cap at 0
	void addSoul(int v);
	//Adds an artefact to the human
	void addArtefact(Artefact* a);
	//Removes an artefact at the selected index
	void removeArtefact(int index);
	//Resets the soul count to 0
	inline void resetSoulCount() { m_souls = 0; }

	//Gets the number of souls the human player has collected
	inline int getSouls() { return m_souls; }
	//Gets the artefacts that the human has
	inline std::vector<Artefact*> getArtefacts() { return m_artefact; }

	//Returns true
	bool isHuman();
};