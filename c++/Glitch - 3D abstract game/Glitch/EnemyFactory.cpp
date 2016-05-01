#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(MeshManager* mManager, Player* player, Mesh* bullet, Mesh* enemyBullet, Difficulty difficulty, int level)
	: Factory(mManager)
{
	m_difficulty = difficulty;
	m_level = level;

	m_player = player;
	m_bullet = bullet;
	m_enemyBullet = enemyBullet;

	m_incr = 0;
	m_newLevel = false;

	srand(time(NULL));
}

void EnemyFactory::setLevel(int newLevel)
{
	if (newLevel > 0)
	{
		if (m_level != newLevel)
		{
			m_newLevel = true;
		}

		m_level = newLevel;
	}
}

GameObject* EnemyFactory::getObject()
{
	//Spawn logic
	while (true)
	{
		int percentage = rand() % 100 + 1;

		if (m_level % 5 == 0 && m_newLevel)
		{
			if (m_difficulty == Difficulty::normal)
			{
				m_incr += 0.5;
			}
			else if (m_difficulty == Difficulty::advanced)
			{
				m_incr += 0.75;
			}
			
			m_newLevel = false;
		}

		//Increase stats and points the higher the level you go
		float speedIncr = m_incr * (m_level - 3);
		float dmgIncr = m_level - 8 <= 0 ? 0 : m_incr * (m_level - 8) * 0.25;
		float pointIncr = m_incr * 15 * (m_level / 2);
		//Only increase hp after level 12
		int hpIncr = m_level - 12 <= 0 ? 0 : m_incr * (m_level - 12) * 0.5;

		if (m_level >= 1 && percentage <= 65)
		{
			//Green enemy
			if (m_difficulty == Difficulty::normal)
			{
				return new GreenEnemy(m_mManager->getMesh("green"), m_player, m_difficulty, 1.0f, 10 + pointIncr / 1.25, 1 + hpIncr, 5 + dmgIncr, (rand() % 6 + 13) + speedIncr / 2.5);
			}
			else if (m_difficulty == Difficulty::advanced)
			{
				return new GreenEnemy(m_mManager->getMesh("green"), m_player, m_difficulty, 0.7f, 10 + pointIncr / 1.25, 1 + hpIncr * 1.5, 10 + dmgIncr, (rand() % 6 + 15) + speedIncr / 1.5);
			}
		}
		else if (m_level >= 2 && percentage > 65 && percentage <= 85)
		{
			//Blue monster
			if (m_difficulty == Difficulty::normal)
			{
				return new BlueEnemy(m_mManager->getMesh("blue"), m_player, m_enemyBullet, m_difficulty, 2.0f, 50 + pointIncr, 2 + hpIncr, 1 + dmgIncr, 10);
			}
			else if (m_difficulty == Difficulty::advanced)
			{
				return new BlueEnemy(m_mManager->getMesh("blue"), m_player, m_enemyBullet, m_difficulty, 1.5f, 45 + pointIncr, 3 + hpIncr * 1.5, 4 + dmgIncr, 10);
			}
		}
		else if (m_level >= 7 && percentage > 85 && percentage <= 95)
		{
			//Red monster
			if (m_difficulty == Difficulty::normal)
			{
				return new RedEnemy(m_mManager->getMesh("red"), m_player, m_mManager->getMesh("level"), m_difficulty, 2.5f, 35 + pointIncr / 1.25, 3 + hpIncr * 1.25, 25 + dmgIncr, 8 + speedIncr / 2.5);
			}
			else if (m_difficulty == Difficulty::advanced)
			{
				return new RedEnemy(m_mManager->getMesh("red"), m_player, m_mManager->getMesh("level"), m_difficulty, 3.0f, 45 + pointIncr / 1.25, 4 + hpIncr * 1.25, 25 + dmgIncr * 2, 6 + speedIncr / 2);
			}
		}
		else if (m_level >= 12 && percentage > 95 && percentage <= 100)
		{
			//Purple monster
			if (m_difficulty == Difficulty::normal)
			{
				return new PurpleEnemy(m_mManager->getMesh("purple"), m_player, m_mManager, this, m_difficulty, 3.0f, 25 + pointIncr, 1 + hpIncr * 1.5, 10 + dmgIncr, 8);
			}
			else if (m_difficulty == Difficulty::advanced)
			{
				return new PurpleEnemy(m_mManager->getMesh("purple"), m_player, m_mManager, this, m_difficulty, 2.5f, 20 + pointIncr, 2 + hpIncr * 2, 20 + dmgIncr, 10);
			}
		}
	}
}