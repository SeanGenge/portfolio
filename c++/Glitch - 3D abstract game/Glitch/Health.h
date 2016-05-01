#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Collisions.h"
#include "SoundManager.h"

/*
	Gives the player health when they walk through them. The amount of health depends on the health bonus
*/

class Player;

class Health : public GameObject
{
private:
	//Bounding box
	CBoundingBox* m_bBox;

	//The default min and max of the bounding box
	Vector3 m_bBoxMin;
	Vector3 m_bBoxMax;

	//Sounds
	Sound* m_pickup;

	//whether the hp should be moving up (y direction) or down. Makes it bob
	bool m_moveUp;

	int m_speed;

	//Health bonus
	int m_healthBonus;

	//Destroy timer
	float m_maxDestroyTimer;
	float m_destroyTimer;

	//Update timer
	inline void updateTimer(float timestep, float& timer);

	//Collision code for different objects
	inline void collisionPlayer(Player* player);
	inline void collisionLevel(Level* g, float timestep);

public:
	//You pass the global camera in for the player to move it as it's eyes
	Health(Mesh* mesh, SoundManager* sManager);

	//Get the bounding box
	CBoundingBox* getBBox() { return m_bBox; }
	//Updates the bounding box
	inline void updateBBox();

	void setHealthBonus(int health) { m_healthBonus = health; }
	int getHealthBonus() { return m_healthBonus; }

	void collision(GameObject* g, float timestep);

	void reset();

	void update(float timestep);
};