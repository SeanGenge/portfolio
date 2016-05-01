#include "Health.h"

Health::Health(Mesh* mesh, SoundManager* sManager)
	: GameObject(mesh)
{
	m_type = "health";

	//Starting health bonus
	m_healthBonus = 15;

	m_bBoxMin = mesh->getMin();
	m_bBoxMax = mesh->getMax();

	m_pickup = sManager->GetSound("Assets/Sounds/health.wav");

	m_bBox = new CBoundingBox(m_bBoxMin, m_bBoxMax);

	m_moveUp = true;
	m_speed = 8;

	m_maxDestroyTimer = 20.0f;
	m_destroyTimer = m_maxDestroyTimer;
}

void Health::updateBBox()
{
	m_bBox->SetMin(m_bBoxMin + m_position);
	m_bBox->SetMax(m_bBoxMax + m_position);
}

void Health::update(float timestep)
{
	updateTimer(timestep, m_destroyTimer);

	addRotation(Vector3(0, -50 * timestep, 0));

	if (m_destroyTimer == 0)
	{
		m_destroy = true;
	}

	updateBBox();
}

void Health::updateTimer(float timestep, float& timer)
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

void Health::collision(GameObject* g, float timestep)
{
	std::string type = g->getType();

	if (type == "player")
	{
		collisionPlayer(static_cast<Player*>(g));
	}
	else if (type == "level")
	{
		collisionLevel(static_cast<Level*>(g), timestep);
	}
}

void Health::collisionPlayer(Player* g)
{
	if (CheckCollision(*g->getBBox(), *getBBox()))
	{
		m_destroy = true;
		m_pickup->Play();
	}
}

void Health::collisionLevel(Level* g, float timestep)
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

void Health::reset()
{
	GameObject::reset();

	m_destroyTimer = m_maxDestroyTimer;
}