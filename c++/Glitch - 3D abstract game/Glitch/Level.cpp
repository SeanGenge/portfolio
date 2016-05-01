#include "Level.h"

Level::Level(Mesh* mesh, int sizeXZ, int sizeY)
	: GameObject(mesh)
{
	m_type = "level";

	if (sizeXZ <= 1)
		sizeXZ = 1;
	if (sizeY <= 1)
		sizeY = 1;

	//Scale the level to fit size
	setScale(Vector3(sizeXZ, sizeY, sizeXZ));

	m_min = Vector3(mesh->getMin().x * sizeXZ, mesh->getMin().y, mesh->getMin().z * sizeXZ);
	m_max = Vector3(mesh->getMax().x * sizeXZ, mesh->getMax().y * sizeY, mesh->getMax().z * sizeXZ);

	//Set up the boundaries of the level
	m_lWall = new CPlane(Vector3::Right, abs(mesh->getMin().x )* sizeXZ);
	m_rWall = new CPlane(Vector3::Left, mesh->getMax().x * sizeXZ);
	m_fWall = new CPlane(Vector3::Backward, abs(mesh->getMin().z) * sizeXZ);
	m_bWall = new CPlane(Vector3::Forward, mesh->getMax().z * sizeXZ);
	m_floor = new CPlane(Vector3::Up, mesh->getMin().y);
}

void Level::update(float timestep)
{

}