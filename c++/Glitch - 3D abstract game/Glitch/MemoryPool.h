#pragma once

/*
Purpose: Holds a selected number of objects for quick use. eg. Bullets
*/

#include <vector>

//Object - The object you want to create
template<class Object>
class MemoryPool
{
protected:
	typedef std::vector<std::pair<Object*, bool>> pool;

	//Holds x amount of objects ready for use. Fixed size
	//Object - object being stored, bool - If the object is in use
	std::vector<std::pair<Object*, bool>> m_pool;

	virtual void initialize() = 0;

public:
	//Retrieves an object if one is available. Returns NULL if no object is free
	Object* getObject()
	{
		for (pool::iterator i = m_pool.begin(); i != m_pool.end(); i++)
		{
			if (i->second == false)
			{
				i->second = true;
				return i->first;
			}
		}

		return NULL;
	}

	//Use this to set the object as usable again
	virtual Object* finished(Object* obj)
	{
		//Returns the object in the pool if found else return NULL
		for (pool::iterator i = m_pool.begin(); i != m_pool.end(); i++)
		{
			if (i->first == obj)
			{
				i->second = false;

				return obj;
			}
		}

		return NULL;
	}

	void getSize() { return m_pool.size(); }
};