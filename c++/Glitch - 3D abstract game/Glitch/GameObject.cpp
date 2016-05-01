#include "GameObject.h"

GameObject::GameObject(Mesh* mesh)
{
	initialize(mesh, Vector3::Zero, Vector3::Zero, Vector3(1, 1, 1));
}

GameObject::GameObject(Mesh* mesh, Vector3 position)
{
	initialize(mesh, position, Vector3::Zero, Vector3(1, 1, 1));
}

GameObject::GameObject(Mesh* mesh, Vector3 position, Vector3 rotation)
{
	initialize(mesh, position, rotation, Vector3(1, 1, 1));
}

GameObject::GameObject(Mesh* mesh, Vector3 position, Vector3 rotation, Vector3 scale)
{
	initialize(mesh, position, rotation, scale);
}

void GameObject::initialize(Mesh* mesh, Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_type = "";

	m_mesh = mesh;

	m_defPosition = position;
	m_defRotation = rotation;
	m_defScale = scale;

	//Sets the position, rotation and scale of the object to the default positions
	//Also sets m_destroy to false (don't destroy the object
	reset();
}

void GameObject::addRotation(Vector3 rotation)
{
	m_rotation += rotation;

	//Checks if the values are above 360 and bring them down
	while (m_rotation.x >= 360.0f)
	{
		m_rotation.x -= 360.0f;
	}

	while (m_rotation.y >= 360.0f)
	{
		m_rotation.y -= 360.0f;
	}

	while (m_rotation.z >= 360.0f)
	{
		m_rotation.z -= 360.0f;
	}
}

void GameObject::collision(GameObject* g, float timestep)
{

}

void GameObject::render(Direct3D* renderer, Camera* camera)
{
	Matrix scale = Matrix::CreateScale(m_scale);
	Matrix rotation = Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(m_rotation.y), DirectX::XMConvertToRadians(m_rotation.x), DirectX::XMConvertToRadians(m_rotation.z));
	Matrix position = Matrix::CreateTranslation(m_position);
	Matrix world = scale * rotation * position;

	m_mesh->Render(renderer, world, camera);
}

void GameObject::handleInput(float timestep, InputController* input)
{

}

void GameObject::reset()
{
	m_position = m_defPosition;
	m_rotation = m_defRotation;
	m_scale = m_defScale;

	m_destroy = false;
}