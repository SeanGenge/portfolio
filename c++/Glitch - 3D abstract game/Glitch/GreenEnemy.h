#pragma once

#include <ctime>
#include <cstdlib>

#include "Enemy.h"

class GreenEnemy : public Enemy
{
private:
	//The length of time the timestep will last for
	float m_maxSideStepTimer;
	float m_sideStepTimer;

	//If the enemy will move left or right
	bool m_goLeft;
	//Left and right speed
	float m_sidestepSpeed;
	//The distance from the enemy
	Vector3 m_distance;
	//The left vector of the enemy
	Vector3 m_left;

	//After x seconds, the enemy self detonates. No damage. Prevents this enemy all cluttering together since it just follows the player and gives more interesting gameplay
	float m_maxDestroyTimer;
	float m_destroyTimer;

	//The advanced move set
	void advanced(float timestep);
	//The normal move set
	void normal(float timestep);

	void followPlayer(float timestep);
	void sidestep(float timstep);

	void collisionPlayer(Player* g);

	//Update timer
	inline void updateTimer(float timestep, float& timer);

	void update(float timestep);

public:
	GreenEnemy(Mesh* mesh, Player* player, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed);
};