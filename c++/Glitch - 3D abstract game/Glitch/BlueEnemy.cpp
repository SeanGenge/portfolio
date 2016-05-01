#include "BlueEnemy.h"

/*
	normal - Stays in the air and shoots slow missiles
	advanced - Same as normal except faster cooldown of bullets and more hp, dmg etc
*/

BlueEnemy::BlueEnemy(Mesh* mesh, Player* player, Mesh* bullet, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed)
	: Enemy(mesh, player, difficulty, scale, points, maxHealth, damage, speed)
{
	if (m_difficulty == Difficulty::normal)
	{
		m_maxBulletCooldown = 2.0f;
	}
	else if (m_difficulty == Difficulty::advanced)
	{
		m_maxBulletCooldown = 1.5f;
	}

	//Don't fire as soon as the enemy is spawned
	m_bulletCooldown = 2.5f;

	m_yPos = rand() % 7 + 5;

	m_bulletPool = new ObjectPool<Bullet>(6, bullet);
}

void BlueEnemy::advanced(float timestep)
{

}

void BlueEnemy::normal(float timestep)
{
	
}

void BlueEnemy::checkDestroyBullets()
{
	for (std::vector<Bullet*>::iterator i = m_bulletDestroy.begin(); i != m_bulletDestroy.end(); i++)
	{
		if ((*i)->checkDestroy())
		{
			m_bulletPool->finished(*i);
		}
	}
}

Bullet* BlueEnemy::shootMissile()
{
	if (m_bulletCooldown == 0)
	{
		Bullet* bullet = m_bulletPool->getObject();

		if (bullet != NULL)
		{
			m_bulletDestroy.push_back(bullet);

			//Set the bullets position to the enemy shooting
			bullet->setPosition(m_position);
			//Make sure the owner is an enemy
			bullet->setOwner(false);
			//Slow down the bullet
			bullet->setSpeed(80);
			bullet->setDamage(m_damage);

			//Get a matrix to look at the player
			Matrix lookAt = Matrix::CreateLookAt(m_position, m_player->getPosition(), Vector3::Up);

			//Calculate x rotation
			float xRot = atan2(lookAt._32, lookAt._33) * (180 / DirectX::XM_PI);
			if (xRot > 0)
			{
				xRot *= -1;
				xRot -= 2;
			}
			else
			{
				xRot += 2;
			}
			//Calculate y rotation
			float yRot = atan2(lookAt._13, lookAt._33) * (180 / DirectX::XM_PI);
			if (yRot > 90) yRot -= 180;
			if (yRot < -90) yRot += 180;

			//Update rotation
			bullet->setRotation(Vector3(xRot, yRot, 0));

			m_bulletCooldown = m_maxBulletCooldown;

			return bullet;
		}
	}

	return NULL;
}

void BlueEnemy::updateMissileTimer(float timestep)
{
	if (m_bulletCooldown - timestep <= 0)
	{
		m_bulletCooldown = 0;
	}
	else
	{
		m_bulletCooldown -= timestep;
	}
}

GameObject* BlueEnemy::getObject()
{
	return shootMissile();
}

void BlueEnemy::update(float timestep)
{
	checkDestroyBullets();
	
	Enemy::update(timestep);

	updateMissileTimer(timestep);
	
	//Make sure the enemies position is always above 6 for the y-axis
	if (m_position.y < m_yPos)
	{
		addPosition(Vector3(0, m_speed * timestep, 0));
	}
	else if (m_position.y > m_yPos)
	{
		addPosition(Vector3(0, -m_speed * timestep, 0));
	}

	addRotation(Vector3(0, 75.0 * timestep, 0));
}