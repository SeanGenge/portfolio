#include "GreenEnemy.h"

/*
	normal - Follows player
	advanced - Follows player but also moves from side to side. Makes it harder to aim at this target
	This enemy dies on contact with the player and deals damage
*/

GreenEnemy::GreenEnemy(Mesh* mesh, Player* player, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed)
	: Enemy(mesh, player, difficulty, scale, points, maxHealth, damage, speed)
{
	srand(time(NULL));
	m_goLeft = rand() % 100 + 1 <= 50 ? true : false;

	m_distance = Vector3::Zero;
	m_left = Vector3::Zero;
	m_sidestepSpeed = rand() % 7 + 5;

	//Get a random number between 0 and 1
	m_maxSideStepTimer = ((float)rand() / RAND_MAX);
	m_sideStepTimer = m_maxSideStepTimer;

	m_maxDestroyTimer = rand() % 15 + 5;
	m_destroyTimer = m_maxDestroyTimer;
}

void GreenEnemy::advanced(float timestep)
{
	updateTimer(timestep, m_sideStepTimer);

	followPlayer(timestep);
	sidestep(timestep);

	if (m_sideStepTimer == 0)
	{
		//Go in the other direction
		m_goLeft = m_goLeft ? false : true;
		m_sideStepTimer = m_maxSideStepTimer;
	}
}

void GreenEnemy::normal(float timestep)
{
	followPlayer(timestep);
}

void GreenEnemy::collisionPlayer(Player* g)
{
	if (CheckCollision(*m_bBox, *g->getBBox()))
	{
		//Kill the enemy
		m_destroy = true;
	}
}

void GreenEnemy::updateTimer(float timestep, float& timer)
{
	//Decrease timer
	if (timer != 0)
	{
		if (timer - timestep <= 0)
		{
			timer = 0;
		}
		else
		{
			timer -= timestep;
		}

	}
}

void GreenEnemy::followPlayer(float timestep)
{
	m_distance = m_player->getPosition() - (m_position + Vector3(0, -5.0f, 0));
	m_distance.Normalize();

	addPosition(m_distance * m_speed * timestep);
}

void GreenEnemy::sidestep(float timestep)
{
	if (m_goLeft)
	{
		m_left = m_distance.Cross(Vector3::Up);
	}
	else
	{
		//In this case, the left is now the right
		m_left = m_distance.Cross(Vector3::Up) * -1;
	}

	addPosition(m_left * m_sidestepSpeed * timestep);
}

void GreenEnemy::update(float timestep)
{
	updateTimer(timestep, m_destroyTimer);

	Enemy::update(timestep);

	if (m_destroyTimer == 0)
	{
		m_destroy = true;
	}
}