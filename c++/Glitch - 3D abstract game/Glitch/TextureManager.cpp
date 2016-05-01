#include "TextureManager.h"

void TextureManager::registerTexture(std::string id, Texture* mesh)
{
	assert(m_manager[id] == 0);

	m_manager[id] = mesh;
}

Texture* TextureManager::getTexture(std::string id)
{
	assert(m_manager[id] != 0);

	return m_manager[id];
}

void TextureManager::shutdown()
{
	for (map::iterator i = m_manager.begin(); i != m_manager.end(); i++)
	{
		i->second->Release();
		delete i->second;
	}

	m_manager.clear();
}