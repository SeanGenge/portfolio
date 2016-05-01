#include "PurpleEnemy.h"

/*
	normal - Teleports around the map. Spawns green, blue or red enemies
	advanced - Same as normal except the time is decreased
*/

PurpleEnemy::PurpleEnemy(Mesh* mesh, Player* player, MeshManager* mManager, EnemyFactory* ef, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed)
	: Enemy(mesh, player, difficulty, scale, points, maxHealth, damage, speed)
{
	srand(time(NULL));

	m_ef = ef;

	if (m_difficulty == Difficulty::normal)
	{
		m_maxTeleportCooldown = rand() % 4 + 2;
		m_teleportCooldown = m_maxTeleportCooldown;

		m_maxEnemySpawnCooldown = rand() % 2 + 4;
		m_enemySpawnCooldown = m_maxEnemySpawnCooldown;
	}
	else if (m_difficulty == Difficulty::advanced)
	{
		m_maxTeleportCooldown = rand() % 2 + 2;
		m_teleportCooldown = m_maxTeleportCooldown;

		m_maxEnemySpawnCooldown = rand() % 2 + 2;
		m_enemySpawnCooldown = m_maxEnemySpawnCooldown;
	}

	m_mManager = mManager;
	m_level = mManager->getMesh("level");

	m_moveUp = true;
}

void PurpleEnemy::advanced(float timestep)
{
	teleport(timestep);
}

void PurpleEnemy::normal(float timestep)
{
	teleport(timestep);
}

void PurpleEnemy::updateTeleportCooldown(float timestep)
{
	if (m_teleportCooldown - timestep < 0)
	{
		m_teleportCooldown = 0;
	}
	else
	{
		m_teleportCooldown -= timestep;
	}
}

void PurpleEnemy::updateEnemySpawnCooldown(float timestep)
{
	if (m_enemySpawnCooldown - timestep < 0)
	{
		m_enemySpawnCooldown = 0;
	}
	else
	{
		m_enemySpawnCooldown -= timestep;
	}
}

void PurpleEnemy::teleport(float timestep)
{
	if (m_teleportCooldown == 0)
	{
		//Does not always need to teleport. Random chance
		int random = rand() % 100 + 1;

		if (random <= 45)
		{
			Vector3 min = m_level->getMin() * 2;
			Vector3 max = m_level->getMax() * 2;

			//Pick a random location. To prevent collision with the player. Teleports above a seleted y value which is also above the map
			setPosition(Vector3((int)(rand() % (int)(min.x - max.x + 1) + min.x), 20, (int)(rand() % (int)(min.z - max.z + 1) + min.z)));
		}

		m_teleportCooldown = m_maxTeleportCooldown;
	}
}

GameObject* PurpleEnemy::getObject()
{
	int percentage = rand() % 100 + 1;

	if (m_enemySpawnCooldown == 0 && percentage <= 45)
	{
		while (true)
		{
			Enemy* e = static_cast<Enemy*>(m_ef->getObject());

			//Set the position of the enemy slightly lower than the spawning enemy
			e->setPosition(m_position + Vector3(0, -2, 0));

			if (dynamic_cast<PurpleEnemy*>(e) == NULL)
			{
				m_enemySpawnCooldown = m_maxEnemySpawnCooldown;
				return e;
			}
		}
	}
	else return NULL;
}

void PurpleEnemy::update(float timestep)
{
	updateTeleportCooldown(timestep);
	updateEnemySpawnCooldown(timestep);

	//Make the enemy bob up and down
	if (m_moveUp && m_position.y < 22)
	{
		if (m_position.y > 21.5) m_moveUp = false;
		addPosition(Vector3(0, m_speed * timestep, 0));
	}
	else if (!m_moveUp && m_position.y > 16)
	{
		if (m_position.y < 16.5) m_moveUp = true;
		addPosition(Vector3(0, -m_speed * timestep, 0));
	}

	if (m_position.y >= 22) m_moveUp = false;

	addRotation(Vector3(0, 300.0 * timestep, 0));

	Enemy::update(timestep);
}