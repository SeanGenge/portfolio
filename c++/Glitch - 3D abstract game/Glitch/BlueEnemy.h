#pragma once

#include <vector>
#include <cmath>
#include "Enemy.h"
#include "ObjectPool.h"
#include "Bullet.h"

class BlueEnemy : public Enemy
{
private:
	//The maximum time it takes before another missile can be shot
	float m_maxBulletCooldown;
	//The current missile cooldown
	float m_bulletCooldown;

	//Their Y position. Random for every enemy
	float m_yPos;

	ObjectPool<Bullet>* m_bulletPool;
	//Holds all fired bullets. Used to place back into memory pool
	std::vector<Bullet*> m_bulletDestroy;

	//The advanced move set
	void advanced(float timestep);
	//The normal move set
	void normal(float timestep);

	void updateMissileTimer(float timestep);
	Bullet* shootMissile();

	inline void checkDestroyBullets();

public:
	BlueEnemy(Mesh* mesh, Player* player, Mesh* bullet, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed);

	GameObject* getObject();
	void update(float timestep);
};