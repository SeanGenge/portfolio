/*	FIT2049 - Example Code
 *	Collisions.h
 *	Created by Elliott Wilson - 2015 - Monash Univeristy
 *	This header contains all of the Collision objects we can use
 *  Including: Bounding Spheres, Bounding Boxes, Planes and Rays
 *  It also includes the check functions for all of the different
 *  bounding objects.
 */

#ifndef COLLISIONS_H
#define COLLISIONS_H

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

#include "DirectXTK/SimpleMath.h"

using namespace DirectX::SimpleMath;

#define ON_PLANE_AMOUNT 0.001f

//Our plane functions can return one of 3 different values, this enum defines them.
enum PLANE_RESULT
{
	PLANE_IN_FRONT = 0, //Objects can be in front of the plane
	PLANE_ON,           //On the plane
	PLANE_BEHIND        //Or behind the plane
};

//The following classes represent our bounding objects
//Note the C prefix, this is to avoid issues with the Bounding Objects contained within the SimpleMath header
class CBoundingSphere
{
private:
	Vector3 m_center;
	float m_radius;

public:
	CBoundingSphere() { m_center = Vector3::Zero; m_radius = 0; }
	CBoundingSphere(Vector3 center, float radius) { m_center = center; m_radius = radius; }

	Vector3 GetCenter() const { return m_center; }
	float GetRadius() const { return m_radius; }

	void SetCenter(Vector3 center) { m_center = center; }
	void SetRadius(float radius) { m_radius = radius; }
};

class CBoundingBox
{
private:
	Vector3 m_min;
	Vector3 m_max;

public:
	CBoundingBox() { m_min = Vector3::Zero; m_max = Vector3::Zero; }
	CBoundingBox(Vector3 min, Vector3 max) { m_min = min; m_max = max; }

	Vector3 GetMin() const { return m_min; }
	Vector3 GetMax() const { return m_max; }

	void SetMin(Vector3 min) { m_min = min; }
	void SetMax(Vector3 max) { m_max = max; }
};

class CPlane
{
private:
	Vector3 m_normal;
	float m_distance;

public:
	CPlane() { m_normal = Vector3::Zero; m_distance = 0; }
	CPlane(Vector3 normal, float distance) { m_normal = normal; m_distance = distance; }

	Vector3 GetNormal() const { return m_normal; }
	float GetDistance() const { return m_distance; }

	void SetNormal(Vector3 normal) { m_normal = normal; }
	void SetDistance(float distance) { m_distance = distance; }

	void Verify() { m_normal.Normalize(); } //The normal of a plane must be a unit vector. You can use this method to ensure that is true
};

class CRay
{
private:
	Vector3 m_origin;
	Vector3 m_direction;

public:
	CRay() { m_origin = Vector3::Zero; m_direction = Vector3::Zero; }
	CRay(Vector3 origin, Vector3 direction) { m_origin = origin; m_direction = direction; }

	Vector3 GetOrigin() const { return m_origin; }
	Vector3 GetDirection() const { return m_direction; }

	void SetOrigin(Vector3 origin) { m_origin = origin; }
	void SetDirection(Vector3 direction) { m_direction = direction; }

	void Verify() { m_direction.Normalize(); }  //The direction of the ray must be a unit vector. You can use this method to ensure that is true
};

//Collisions with bounding solids
bool CheckCollision(const CBoundingSphere& sphere, const Vector3& point);
bool CheckCollision(const CBoundingSphere& sphere1, const CBoundingSphere& sphere2);
bool CheckCollision(const CBoundingSphere& sphere, const CBoundingBox& bb);
bool CheckCollision(const CBoundingBox& bb, const Vector3& point);
bool CheckCollision(const CBoundingBox& bb1, const CBoundingBox& bb2);

//Collision with planes
PLANE_RESULT CheckPlane(const CPlane& plane, const Vector3& point);
PLANE_RESULT CheckPlane(const CPlane& plane, const CBoundingSphere& sphere);
PLANE_RESULT CheckPlane(const CPlane& plane, const CBoundingBox& bb);

//Collisions with Rays
bool CheckRay(const CRay& ray, const CBoundingSphere& sphere, Vector3* hitPoint);
bool CheckRay(const CRay& ray, const CBoundingBox& bb, Vector3* hitPoint);
bool CheckRay(const CRay& ray, const CPlane& plane, Vector3* hitPoint);

#endif