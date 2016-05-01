#pragma once

/*
	Purpose: Creates the desired object depending on specific logic
*/

#include "MeshManager.h"

//Object - The object you want to create
template<class Object>
class Factory
{
protected:
	//The manager with all the enemy models
	MeshManager* m_mManager;

public:
	//Constructor
	Factory(MeshManager* mManager)
	{
		m_mManager = mManager;
	}

	//Retrieves an object
	virtual Object* getObject() = 0;
};