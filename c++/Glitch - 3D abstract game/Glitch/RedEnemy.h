#pragma once

#include <ctime>
#include <cstdlib>
#include "Enemy.h"

class RedEnemy : public Enemy
{
private:
	//Used to check if the enemy should move again
	Vector3 m_newPos;

	//The min and max of the level
	Vector3 m_min;
	Vector3 m_max;

	//Gets a new position once the timer is up
	float m_maxNewPosTimer;
	float m_newPosTimer;

	inline void move(float timestep);
	void deflect(Bullet* b);

	//The advanced move set
	void advanced(float timestep);
	//The normal move set
	void normal(float timestep);

	void collisionBullet(Bullet* g);

	void updateTimer(float timestep);

public:
	RedEnemy(Mesh* mesh, Player* player, Mesh* level, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed);

	void update(float timestep);
};