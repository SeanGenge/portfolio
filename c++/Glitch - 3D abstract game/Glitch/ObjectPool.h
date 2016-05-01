#pragma once

#include "MemoryPool.h"
#include "GameObject.h"

/*
	This memory pool deals with objects that has a mesh associated with them
*/

template <class Object>
class ObjectPool : public MemoryPool<Object>
{
private:
	Mesh* m_mesh;
	int m_numItems;

	void initialize()
	{
		for (unsigned int i = 0; i < m_numItems; i++)
		{
			m_pool.push_back(std::make_pair(new Object(m_mesh), false));
		}
	}

public:
	ObjectPool(int numItems, Mesh* mesh)
	{
		m_mesh = mesh;

		if (numItems < 1)
			m_numItems = 1;
		else
			m_numItems = numItems;

		initialize();
	}

	Object* finished(Object* obj)
	{
		Object* o = MemoryPool::finished(obj);
		
		if (o != NULL)
		{
			o->reset();
		}

		return o;
	}
};