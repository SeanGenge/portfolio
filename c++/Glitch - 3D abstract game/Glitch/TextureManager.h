#pragma once

#include <map>
#include <string>
#include <assert.h>
#include "Texture.h"

class TextureManager
{
private:
	typedef std::map<std::string, Texture*> map;

	//Holds all the different textures in the manager
	map m_manager;

public:
	void registerTexture(std::string id, Texture* mesh);

	Texture* getTexture(std::string id);

	//Deletes all the textures in the map
	void shutdown();
};