#include "Enemy.h"

Enemy::Enemy(Mesh* mesh, Player* player, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed)
	: GameObject(mesh)
{
	m_difficulty = difficulty;
	m_type = "enemy";
	m_player = player;

	m_points = points;
	m_maxHealth = maxHealth;
	m_currentHealth = m_maxHealth;
	m_speed = speed;
	m_damage = damage;

	m_spawned = false;

	//The enemy starts off as a point
	setScale(Vector3::Zero);
	m_scaleDefault = scale;

	m_boxMinDefault = m_mesh->getMin() * scale;
	m_boxMaxDefault = m_mesh->getMax() * scale;
	
	m_boxMin = Vector3::Zero;
	m_boxMax = Vector3::Zero;
	m_bBox = new CBoundingBox(m_boxMin, m_boxMax);
}

void Enemy::updateBBox()
{
	m_bBox->SetMin(m_boxMin + m_position);
	m_bBox->SetMax(m_boxMax + m_position);
}

void Enemy::setMaxHealth(int newHealth, bool changeCurrentHealth)
{
	m_maxHealth = newHealth;

	if (changeCurrentHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}

void Enemy::damage(float damage)
{
	if (m_currentHealth - damage <= 0)
	{
		m_currentHealth = 0;
	}
	else
	{
		m_currentHealth -= damage;
	}
}

void Enemy::spawn(float timestep)
{
	if (!m_spawned && m_scale.x > m_scaleDefault)
	{
		m_boxMin = m_boxMinDefault;
		m_boxMax = m_boxMaxDefault;

		m_bBox->SetMin(m_boxMin);
		m_bBox->SetMax(m_boxMax);
		setScale(Vector3(m_scaleDefault, m_scaleDefault, m_scaleDefault));

		m_spawned = true;
	}
	else if (!m_spawned)
	{
		//Might not be super accurate but will still work since the spawning phase is very fast
		Vector3 dMin = m_boxMinDefault;
		dMin.Normalize();

		m_boxMin += dMin * timestep;
		m_boxMax += dMin * timestep * -1;

		m_bBox->SetMin(m_boxMin);
		m_bBox->SetMax(m_boxMax);
		addScale(Vector3(timestep, timestep, timestep));
	}
}

GameObject* Enemy::getObject()
{
	//Default
	return NULL;
}

void Enemy::update(float timestep)
{
	spawn(timestep);

	if (m_difficulty == Difficulty::normal)
	{
		normal(timestep);
	}
	else if (m_difficulty == Difficulty::advanced)
	{
		advanced(timestep);
	}

	updateBBox();
}

void Enemy::collision(GameObject* g, float timestep)
{
	std::string type = g->getType();

	if (type == "enemy")
	{
		collisionEnemy(static_cast<Enemy*>(g));
	}
	else if (type == "level")
	{
		collisionLevel(static_cast<Level*>(g), timestep);
	}
	else if (type == "bullet")
	{
		collisionBullet(static_cast<Bullet*>(g));
	}
	else if (type == "player")
	{
		collisionPlayer(static_cast<Player*>(g));
	}
}

void Enemy::collisionPlayer(Player* p)
{
	
}

void Enemy::collisionEnemy(Enemy* g)
{
	

}

void Enemy::collisionLevel(Level* g, float timestep)
{
	//Back wall
	while (CheckPlane(*g->getBackWall(), *m_bBox) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(0, 0, m_speed * timestep * -1));
		updateBBox();
	}
	//Front wall
	while (CheckPlane(*g->getFrontWall(), *m_bBox) != PLANE_IN_FRONT)
	{

		addPosition(Vector3(0, 0, m_speed * timestep));
		updateBBox();
	}
	//Left wall
	while (CheckPlane(*g->getLeftWall(), *m_bBox) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(m_speed * timestep, 0, 0));
		updateBBox();
	}
	//Right wall
	while (CheckPlane(*g->getRightWall(), *m_bBox) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(m_speed * timestep * -1, 0, 0));
		updateBBox();
	}
	//Floor
	while (CheckPlane(*g->getFloor(), *m_bBox) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(0, m_speed * timestep, 0));
		updateBBox();
	}
}

void Enemy::collisionBullet(Bullet* g)
{
	//Check if it is a player bullet. Enemy bullets pass through enemies
	if (g->getOwner() && CheckCollision(*m_bBox, *g->getBBox()))
	{
		damage(g->getDamage());
		
		if (dead())
		{
			m_destroy = true;
		}
		else
		{
			int a = 0;
		}
	}
}