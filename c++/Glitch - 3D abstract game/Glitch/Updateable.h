#pragma once

/*
	Purpose: Inherit from this class if the sub class can update itself
*/

#include <vector>

template<class Object>
class Updateable
{
private:
	//Contains all the updateable objects in the current state
	std::vector<Object*> m_updateableObjects;

protected:
	void clearUpdater() { m_updateableObjects.clear(); }
	void updateObject(Object* obj) { m_updateableObjects.push_back(obj); }
	//Checks whether a given game object is updated
	bool checkUpdated(Object* obj)
	{
		for (std::vector<Object*>::iterator i = m_updateableObjects.begin(); i != m_updateableObjects.end(); i++)
		{
			if ((*i) == obj)
			{
				return true;
			}
		}

		return false;
	}
	//Returns true if object is removed successfully and false if not in updated objects
	bool removeFromUpdater(Object* obj)
	{
		for (std::vector<Object*>::iterator i = m_updateableObjects.begin(); i != m_updateableObjects.end(); i++)
		{
			if ((*i) == obj)
			{
				m_updateableObjects.erase(i);
				return true;
			}
		}

		return false;
	}

public:
	virtual void onUpdate(float timestep)
	{
		for (std::vector<Object*>::iterator i = m_updateableObjects.begin(); i != m_updateableObjects.end(); i++)
		{
			(*i)->update(timestep);
		}
	}
};