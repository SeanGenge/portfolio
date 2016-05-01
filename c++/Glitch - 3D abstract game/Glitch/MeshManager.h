#pragma once

#include <map>
#include <string>
#include <assert.h>
#include "Mesh.h"

class MeshManager
{
private:
	typedef std::map<std::string, Mesh*> map;

	//Holds all the different meshes in the manager
	map m_manager;
	
public:
	void registerMesh(std::string id, Mesh* mesh);

	Mesh* getMesh(std::string id);

	//Deletes all the meshes in the map
	void shutdown();
};