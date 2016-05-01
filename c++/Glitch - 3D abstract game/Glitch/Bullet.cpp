#include "Bullet.h"

Bullet::Bullet(Mesh* mesh)
	: GameObject(mesh)
{
	//Default values
	m_speed = 250.0f;
	m_damage = 1;
	m_penetration = 1;

	m_type = "bullet";

	m_maxDestroyBulletTimer = 5.0f;
	m_destroyBulletTimer = m_maxDestroyBulletTimer;

	m_destroy = false;
	m_playerBullet = false;

	m_bBoxMin = mesh->getMin();
	m_bBoxMax = mesh->getMax();

	m_bBox = new CBoundingBox(m_bBoxMin, m_bBoxMax);
}

void Bullet::updateBBox()
{
	m_bBox->SetMin(m_bBoxMin + m_position);
	m_bBox->SetMax(m_bBoxMax + m_position);
}

void Bullet::updateDestroyTimer(float timestep)
{
	if (m_destroyBulletTimer - timestep <= 0)
	{
		m_destroyBulletTimer = 0;
		m_destroy = true;
	}
	else
	{
		m_destroyBulletTimer -= timestep;
	}
}

void Bullet::update(float timestep)
{
	updateDestroyTimer(timestep);

	Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(m_rotation.y), DirectX::XMConvertToRadians(m_rotation.x), DirectX::XMConvertToRadians(m_rotation.z));
	//The direction that the bullet will move in
	Vector3 forward = Vector3::Transform(Vector3::Forward, rotationMatrix);

	m_position += forward * m_speed * timestep;

	updateBBox();
}

void Bullet::collision(GameObject* g, float timestep)
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

void Bullet::collisionEnemy(Enemy* g)
{
	if (getOwner() && CheckCollision(*g->getBBox(), *m_bBox))
	{
		m_penetration -= 1;

		if (m_penetration <= 0)
		{
			m_destroy = true;
		}
	}
}

void Bullet::collisionPlayer(Player* g)
{
	if (!getOwner() && CheckCollision(*g->getBBox(), *m_bBox))
	{
		m_penetration -= 1;

		if (m_penetration <= 0)
		{
			m_destroy = true;
		}
	}
}

void Bullet::collisionLevel(Level* g, float timestep)
{
	//Back wall
	if (CheckPlane(*g->getBackWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		m_destroy = true;
	}
	//Front wall
	if (CheckPlane(*g->getFrontWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		m_destroy = true;
	}
	//Left wall
	if (CheckPlane(*g->getLeftWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		m_destroy = true;
	}
	//Right wall
	if (CheckPlane(*g->getRightWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		m_destroy = true;
	}
	//Floor
	if (CheckPlane(*g->getFloor(), *getBBox()) != PLANE_IN_FRONT)
	{
		m_destroy = true;
	}
}

void Bullet::collisionBullet(Bullet* g)
{
	//Do nothing
	//Kept it in case you want to do some cool bullet collision (Stopping an enemy bullet mid air). Matrix stuff
}

void Bullet::reset()
{
	GameObject::reset();

	m_destroyBulletTimer = m_maxDestroyBulletTimer;
}