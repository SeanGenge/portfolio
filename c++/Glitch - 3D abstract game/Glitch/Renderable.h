#pragma once

/*
	Purpose: Inherit from this class if the sub class can render objects to the screen
*/

#include <vector>
#include "Direct3D.h"
#include "Camera.h"

//Object - The object being rendered
template<class Object>
class Renderable
{
private:
	//Contains all the rendered objects in the current state
	std::vector<Object*> m_renderedObjects;

protected:
	void clearRender() { m_renderedObjects.clear(); }
	void renderObject(Object* obj){ m_renderedObjects.push_back(obj); }
	//Checks whether a given game object is rendered
	bool checkRendered(Object* obj)
	{
		for (std::vector<Object*>::iterator i = m_renderedObjects.begin(); i != m_renderedObjects.end(); i++)
		{
			if ((*i) == obj)
			{
				return true;
			}
		}

		return false;
	}
	//Returns true if object is removed successfully and false if not in rendered objects
	bool removeFromRender(Object* obj)
	{
		for (std::vector<Object*>::iterator i = m_renderedObjects.begin(); i != m_renderedObjects.end(); i++)
		{
			if ((*i) == obj)
			{
				m_renderedObjects.erase(i);
				return true;
			}
		}

		return false;
	}

public:
	virtual void onRender(Direct3D* renderer, Camera* camera)
	{
		for (std::vector<Object*>::iterator i = m_renderedObjects.begin(); i != m_renderedObjects.end(); i++)
		{
			(*i)->render(renderer, camera);
		}
	}
};