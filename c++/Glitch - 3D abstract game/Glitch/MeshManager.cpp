#include "MeshManager.h"

void MeshManager::registerMesh(std::string id, Mesh* mesh)
{
	assert(m_manager[id] == 0);

	m_manager[id] = mesh;
}

Mesh* MeshManager::getMesh(std::string id)
{
	assert(m_manager[id] != 0);

	return m_manager[id];
}

void MeshManager::shutdown()
{
	for (map::iterator i = m_manager.begin(); i != m_manager.end(); i++)
	{
		i->second->Release();
		delete i->second;
	}
	
	m_manager.clear();
}