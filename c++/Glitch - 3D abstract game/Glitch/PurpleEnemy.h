#pragma once

#include <ctime>
#include <cstdlib>
#include "Enemy.h"

#include "MeshManager.h"
#include "EnemyFactory.h"

#include "Level.h"

class EnemyFactory;

class PurpleEnemy : public Enemy
{
private:
	EnemyFactory* m_ef;

	//Teleport cooldown
	float m_maxTeleportCooldown;
	float m_teleportCooldown;

	//Enemy spawn timer
	float m_maxEnemySpawnCooldown;
	float m_enemySpawnCooldown;

	//whether the enemy should be moving up (y direction) or down. Makes it bob
	bool m_moveUp;

	//Used to teleport within the boundaries of the level
	Mesh* m_level;
	MeshManager* m_mManager;

	//The advanced move set
	void advanced(float timestep);
	//The normal move set
	void normal(float timestep);

	void teleport(float timestep);
	void updateTeleportCooldown(float timestep);
	void updateEnemySpawnCooldown(float timestep);

public:
	PurpleEnemy(Mesh* mesh, Player* player, MeshManager* mManager, EnemyFactory* ef, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed);

	GameObject* getObject();
	void update(float timestep);
};