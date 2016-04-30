#include "Human.h"

Human* Human::_human = NULL;

Human::Human(std::string name, double hp, double att, double def, int speed) : Player(name, hp, att, def, speed)
{
	m_artefact.clear();
	m_souls = 0;
}

Human* Human::getHumanObject(std::string name, double hp, double att, double def, int speed)
{
	if (_human == NULL) _human = new Human(name, hp, att, def, speed);

	return _human;
}

void Human::removeArtefact(int index)
{
	m_artefact.erase(m_artefact.begin() + index);
}

void Human::deleteHuman()
{
	if (_human != NULL)
	{
		m_artefact.clear();
		delete _human;
		_human = NULL;
	}
}

void Human::addSoul(int v)
{
	if (m_souls + v >= 0)m_souls += v;
	else m_souls = 0;
}

void Human::addArtefact(Artefact* a)
{
	m_artefact.push_back(a);
}

void Human::setName(std::string newName)
{
	m_name = newName;
}

bool Human::isHuman()
{
	return true;
}