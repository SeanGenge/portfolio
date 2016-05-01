#pragma once

#include "InputController.h"

template<class Object>
class Inputable
{
private:
	//Contains all the inputable objects in the current state
	std::vector<Object*> m_inputObjects;

protected:
	void clearInput() { m_inputObjects.clear(); }
	void inputObject(Object* obj) { m_inputObjects.push_back(obj); }
	//Checks whether a given game object is updated
	bool checkInput(Object* obj)
	{
		for (std::vector<Object*>::iterator i = m_inputObjects.begin(); i != m_inputObjects.end(); i++)
		{
			if ((*i) == obj)
			{
				return true;
			}
		}

		return false;
	}
	//Returns true if object is removed successfully and false if not in rendered objects
	bool removeFromInput(Object* obj)
	{
		for (std::vector<Object*>::iterator i = m_inputObjects.begin(); i != m_inputObjects.end(); i++)
		{
			if ((*i) == obj)
			{
				m_inputObjects.erase(i);
				return true;
			}
		}

		return false;
	}

public:
	virtual void handleInput(float timestep, InputController* input)
	{
		for (std::vector<Object*>::iterator i = m_inputObjects.begin(); i != m_inputObjects.end(); i++)
		{
			(*i)->handleInput(timestep, input);
		}
	}
};