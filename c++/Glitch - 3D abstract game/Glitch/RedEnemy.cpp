#include "RedEnemy.h"

/*
	normal - An obstacle that deals damage if touched. Moves to random locations at fast speed
	advanced - Has a 45% chance to deflect bullets. The deflected bullets will deal 2x damage (enemy damage) to the player
*/

RedEnemy::RedEnemy(Mesh* mesh, Player* player, Mesh* level, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed)
	: Enemy(mesh, player, difficulty, scale, points, maxHealth, damage, speed)
{
	srand(time(NULL));
	m_min = level->getMin() * 2.2;
	m_max = level->getMax() * 2.2;

	if (m_difficulty == Difficulty::normal)
	{
		m_maxNewPosTimer = rand() % 4 + 4;
	}
	else if (m_difficulty == Difficulty::advanced)
	{
		m_maxNewPosTimer = rand() % 3 + 2;
	}
	m_newPosTimer = 0;
}

void RedEnemy::advanced(float timestep)
{
	move(timestep);
}

void RedEnemy::normal(float timestep)
{
	move(timestep);
}

void RedEnemy::move(float timestep)
{
	if (m_newPosTimer == 0)
	{
		//Pick a new random location within the level
		m_newPos = Vector3((int)(rand() % (int)(m_min.x - m_max.x + 1) + m_min.x), 6, (int)(rand() % (int)(m_min.z - m_max.z + 1) + m_min.z));
		m_newPosTimer = m_maxNewPosTimer;
	}
	else
	{
		//Move towards that new position if it is not too close to the wall
		setPosition(Vector3::Lerp(m_position, m_newPos, 0.1 * timestep * m_speed));
	}
}

void RedEnemy::deflect(Bullet* b)
{
	//Has a chance to deflect the bullet which can deal 2x damage to the player
	float percentage = rand() % 100 + 1;

	if (percentage <= 45)
	{
		//Flip the bullet around
		b->setRotation(b->getRotation() += Vector3(0, 180, 180));
		b->setOwner(false);
		b->setDamage(m_damage * 2);
	}
	else
	{
		Enemy::collisionBullet(b);
	}
}

void RedEnemy::updateTimer(float timestep)
{
	if (m_newPosTimer - timestep <= 0)
	{
		m_newPosTimer = 0;
	}
	else
	{
		m_newPosTimer -= timestep;
	}
}

void RedEnemy::collisionBullet(Bullet* g)
{
	if (g->getOwner() && CheckCollision(*m_bBox, *g->getBBox()))
	{
		if (m_difficulty == Difficulty::normal)
		{
			Enemy::collisionBullet(g);
		}
		else if (m_difficulty == Difficulty::advanced)
		{
			deflect(g);
		}
	}
}

void RedEnemy::update(float timestep)
{
	Enemy::update(timestep);

	updateTimer(timestep);

	addRotation(Vector3(0, 120.0 * timestep, 0));
}