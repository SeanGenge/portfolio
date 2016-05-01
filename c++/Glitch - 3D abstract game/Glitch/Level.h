#pragma once

#include "GameObject.h"
#include "Collisions.h"

class Level : public GameObject
{
private:
	//All the five walls that encloses the map
	CPlane* m_lWall;
	CPlane* m_rWall;
	CPlane* m_fWall;
	CPlane* m_bWall;
	CPlane* m_floor;

	Vector3 m_min;
	Vector3 m_max;

public:
	Level(Mesh* mesh, int sizeXZ = 1, int sizeY = 1);

	//Get the walls
	CPlane* getLeftWall() { return m_lWall; }
	CPlane* getRightWall() { return m_rWall; }
	CPlane* getFrontWall() { return m_fWall; }
	CPlane* getBackWall() { return m_bWall; }
	CPlane* getFloor() { return m_floor; }

	Vector3 getMin() { return m_min; }
	Vector3 getMax() { return m_max; }

	void update(float timestep);
};