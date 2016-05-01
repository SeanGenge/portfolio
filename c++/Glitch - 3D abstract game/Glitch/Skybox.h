#pragma once

#include "GameObject.h"

class Skybox : public GameObject
{
public:
	Skybox(Mesh* mesh);

	void update(float timestep);
};