#pragma once

/*
	Purpose: Represents a visible game object on the screen with a mesh, position, rotation and scale
*/

#include <string>
#include "Direct3D.h"
#include "Mesh.h"
#include "InputController.h"
#include "Camera.h"

class GameObject
{
private:
	void initialize(Mesh* mesh, Vector3 position, Vector3 rotation, Vector3 scale);

protected:
	Mesh* m_mesh;
	Vector3 m_position;
	//Is in degrees
	Vector3 m_rotation;
	Vector3 m_scale;

	//All the default values
	Vector3 m_defPosition;
	//Is in degrees
	Vector3 m_defRotation;
	Vector3 m_defScale;

	bool m_destroy;

	std::string m_type;

public:
	//Constructors
	GameObject(Mesh* mesh);
	GameObject(Mesh* mesh, Vector3 position);
	GameObject(Mesh* mesh, Vector3 position, Vector3 rotation);
	GameObject(Mesh* mesh, Vector3 position, Vector3 rotation, Vector3 scale);

	//Resets the game object to it's default values
	virtual void reset();

	//Mutators
	void setPosition(Vector3 position) { m_position = position; }
	void setRotation(Vector3 rotation) { m_rotation = rotation; }
	void setScale(Vector3 scale) { m_scale = scale; }
	void setMesh(Mesh* mesh) { m_mesh = mesh; }
	void setType(std::string type) { m_type = type; }

	void addPosition(Vector3 position) { m_position += position; }
	void addRotation(Vector3 rotation);
	void addScale(Vector3 scale) { m_scale += scale; }

	void setDestroy(bool destroy) { m_destroy = destroy; }
	bool checkDestroy() { return m_destroy; }

	//Accessors
	Mesh* getMesh() { return m_mesh; }
	Vector3 getPosition() { return m_position; }
	//Returns a vector where the values are in degrees
	Vector3 getRotation() { return m_rotation; }
	Vector3 getScale() { return m_scale; }
	std::string getType() { return m_type; }

	//Checks if the current game object collides with this selected game object
	virtual void collision(GameObject* g, float timestep);

	virtual void update(float timestep) = 0;
	//Used to capture input
	virtual void handleInput(float timestep, InputController* input);
	virtual void render(Direct3D* renderer, Camera* camera);
};