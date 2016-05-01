/*	FIT2049 - Example Code
*	Camera.cpp
*	Created by Elliott Wilson - 2015 - Monash Univeristy
*	Implementation of Camera.h
*/

#include "Collisions.h"

#include <DirectXMath.h>

//Takes a point and returns the closest point within the bounding box to that initial point
Vector3 ClosestPointInBoundingBox(const CBoundingBox& bb, const Vector3& point)
{
	Vector3 result = point;
    //If the values of the point on each axis are outside of the min and max of the bounding
    //box then we bound the new point to either the min or max values
	if (point.x < bb.GetMin().x)
		result.x = bb.GetMin().x;
	else if (point.x > bb.GetMax().x)
		result.x = bb.GetMax().x;

	if (point.y < bb.GetMin().y)
		result.y = bb.GetMin().y;
	else if (point.y > bb.GetMax().y)
		result.y = bb.GetMax().y;

	if (point.z < bb.GetMin().z)
		result.z = bb.GetMin().z;
	else if (point.z > bb.GetMax().z)
		result.z = bb.GetMax().z;

	return result;
}

bool CheckCollision(const CBoundingSphere& sphere, const Vector3& point)
{
    //The distance between the sphere center and the point must be less than the radius
	return Vector3::Distance(sphere.GetCenter(), point) <= sphere.GetRadius();
}
bool CheckCollision(const CBoundingSphere& sphere1, const CBoundingSphere& sphere2)
{
    //The distance between the centers of the spheres must be less than the sum of the two radii
	return Vector3::Distance(sphere1.GetCenter(), sphere2.GetCenter()) <= (sphere1.GetRadius() + sphere2.GetRadius());
}
bool CheckCollision(const CBoundingSphere& sphere, const CBoundingBox& bb)
{
    //The distance between the closest point within the box and the center of the sphere must be less then the radius of the sphere.
 	return Vector3::Distance(ClosestPointInBoundingBox(bb, sphere.GetCenter()), sphere.GetCenter()) <= sphere.GetRadius();
}
bool CheckCollision(const CBoundingBox& bb, const Vector3& point)
{
    //Each value of the point must be within the min and max range
	return (point.x > bb.GetMin().x && point.x < bb.GetMax().x) && 
		   (point.y > bb.GetMin().y && point.y < bb.GetMax().y) && 
		   (point.z > bb.GetMin().z && point.z < bb.GetMax().z);
}
bool CheckCollision(const CBoundingBox& bb1, const CBoundingBox& bb2)
{
    //The max of the first box must be greater than the min of the second and
    //The min of the first box must be less than the max of the second
	return (bb1.GetMax().x > bb2.GetMin().x &&
			bb1.GetMax().y > bb2.GetMin().y &&
			bb1.GetMax().z > bb2.GetMin().z &&
			bb1.GetMin().x < bb2.GetMax().x &&
			bb1.GetMin().y < bb2.GetMax().y &&
			bb1.GetMin().z < bb2.GetMax().z);
}

PLANE_RESULT CheckPlane(const CPlane& plane, const Vector3& point)
{
    //The plane equation is used to find the distance from the point to the plane
	float distance = plane.GetNormal().Dot(point) + plane.GetDistance();
    
    //If the distance is greater than 0 the point is in front
	if (distance > ON_PLANE_AMOUNT)
		return PLANE_IN_FRONT;
	else if (distance < -ON_PLANE_AMOUNT)   //If the distance is less than 0 the point is behind
		return PLANE_BEHIND;
	else
		return PLANE_ON;    //If 0 then the point is on the plane
}
PLANE_RESULT CheckPlane(const CPlane& plane, const CBoundingSphere& sphere)
{
    //The plane equation is used to find the distance from the center of the sphere to the plane
	float distance = plane.GetNormal().Dot(sphere.GetCenter()) + plane.GetDistance();
	
    //If the distance is greater than 0 and greater than the radius then the sphere is in front of the plane
	if (distance > 0 && distance > sphere.GetRadius())
		return PLANE_IN_FRONT;
	else if (distance < 0 && -distance > sphere.GetRadius())    //If the distance is less than 0 and the absolute distance is greater then the radius then the sphere is behind the plane
		return PLANE_BEHIND;
	else
		return PLANE_ON;    //Otherwise the sphere is intersecting the plane

}
PLANE_RESULT CheckPlane(const CPlane& plane, const CBoundingBox& bb)
{
	Vector3 diagMin, diagMax;

    //The first step is to find which points are the min and max of the box in releation to the plane (diagMin and diagMax)
	if (plane.GetNormal().x >= 0)
	{
		diagMin.x = bb.GetMin().x;
		diagMax.x = bb.GetMax().x;
	}
	else
	{
		diagMin.x = bb.GetMax().x;
		diagMax.x = bb.GetMin().x;
	}

	if (plane.GetNormal().y >= 0)
	{
		diagMin.y = bb.GetMin().y;
		diagMax.y = bb.GetMax().y;
	}
	else
	{
		diagMin.y = bb.GetMax().y;
		diagMax.y = bb.GetMin().y;
	}

	if (plane.GetNormal().z >= 0)
	{
		diagMin.z = bb.GetMin().z;
		diagMax.z = bb.GetMax().z;
	}
	else
	{
		diagMin.z = bb.GetMax().z;
		diagMax.z = bb.GetMin().z;
	}

    //If the distance of the min point is greater than 0 then the whole box is in front
	float distanceFromMin = plane.GetNormal().Dot(diagMin) + plane.GetDistance();
	if (distanceFromMin > 0.0f)
		return PLANE_IN_FRONT;

    //If the distance of the max point is less than 0 then the whole box is behind
	float distanceFromMax = plane.GetNormal().Dot(diagMax) + plane.GetDistance();
	if (distanceFromMax < 0.0f)
		return PLANE_BEHIND;

    //Otherwise the box is on!
	return PLANE_ON;
}

//The Ray tracing collisions are harder to do a lot of the algorithms are based off other resources. Check the links in the comments

bool CheckRay(const CRay& ray, const CBoundingSphere& sphere, Vector3* hitPoint)
{
    //This algorithm is adatped from: http://www.cosinekitty.com/raytrace/chapter06_sphere.html
    //It breaks the problem down into the plane equations needed to find the hit points between the ray and sphere
    //To solve this correctly it makes use of a quadratic equation.
	Vector3 displacement = ray.GetOrigin() - sphere.GetCenter();
	float a = ray.GetDirection().LengthSquared();
	float b = 2.0f * displacement.Dot(ray.GetDirection());
	float c = displacement.LengthSquared() - sphere.GetRadius() * sphere.GetRadius();

	float randicand = b*b - 4.0f * a * c;
	//If the quadratic equation comes back as a negitive then there is no hit.
    if (randicand < 0.0f)
	{
		return false;
	}
	

	float root = sqrt(randicand);
	float denom = 2.0 * a;

    //Here we calculate the distance between ray origin and the two hit points (where the ray enters the sphere and where it exits)
	float hit1 = (-b + root) / denom;
	float hit2 = (-b - root) / denom;

    //If both of the hits are negitive then it means that the sphere is behind the origin of the ray so there is no hit
	if (hit1 < 0 && hit2 < 0)
	{
		return false;
	}

	
	if (hitPoint)
	{
        //If we need to know the first hit point on the sphere then we should use hit1, unless it's negative then we use hit2.
        //This would come up in situations where the origin of the ray is within the sphere.
        float firstHitDistance = hit1 < 0 ? hit2 : hit1;
		Vector3 pointOnSphere = (ray.GetDirection() * firstHitDistance) + ray.GetOrigin();
		hitPoint->x = pointOnSphere.x;
		hitPoint->y = pointOnSphere.y;
		hitPoint->z = pointOnSphere.z;
	}
	return true;
}

bool CheckRay(const CRay& ray, const CBoundingBox& bb, Vector3* hitPoint)
{
    //This algorithm is adapted from: http://tavianator.com/fast-branchless-raybounding-box-intersections/
    //Its based on the "Slab Technique" which treats a bounding box as a series of 2 planes in each axis.
    //It finds where the ray lies on each of these planes and compares those values across each axis.
	float tmin = -INFINITY;
	float tmax = INFINITY;

	float tx1 = (bb.GetMin().x - ray.GetOrigin().x) / ray.GetDirection().x;
	float tx2 = (bb.GetMax().x - ray.GetOrigin().x) / ray.GetDirection().x;

	tmin = max(tmin, min(tx1, tx2));
	tmax = min(tmax, max(tx1, tx2));
	
	float ty1 = (bb.GetMin().y - ray.GetOrigin().y) / ray.GetDirection().y;
	float ty2 = (bb.GetMax().y - ray.GetOrigin().y) / ray.GetDirection().y;

	tmin = max(tmin, min(ty1, ty2));
	tmax = min(tmax, max(ty1, ty2));
	
	float tz1 = (bb.GetMin().z - ray.GetOrigin().z) / ray.GetDirection().z;
	float tz2 = (bb.GetMax().z - ray.GetOrigin().z) / ray.GetDirection().z;

	tmin = max(tmin, min(tz1, tz2));
	tmax = min(tmax, max(tz1, tz2));
	
    //We end up with two hit values just like the sphere, if the max hit is less than 0 then it all happened behind the ray origin
	if (tmax < 0)
		return false;

    //If the max hit value is greater than the min hit (as it should be) then we have a hit!
	if (tmax >= tmin)
	{
		if (hitPoint)
		{
            //If we need to know the first hit point on the box then we should use tmin, unless it's negative then we use tmax.
            //This would come up in situations where the origin of the ray is within the box.
			float firstHitDistance = tmin < 0 ? tmax : tmin;
			Vector3 pointOnBox = (ray.GetDirection() * firstHitDistance) + ray.GetOrigin();
		
			hitPoint->x = pointOnBox.x;
			hitPoint->y = pointOnBox.y;
			hitPoint->z = pointOnBox.z;
		}
		return true;
	}
	return false;
}
bool CheckRay(const CRay& ray, const CPlane& plane, Vector3* hitPoint)
{
    //This algorithm is based on the plane equation we saw in the CheckPlane methods
	float planeRayDirection = plane.GetNormal().Dot(ray.GetDirection());

	if (planeRayDirection == 0)
	{
		return false;
	}

    //The equation is between the plane normal and the ray origin. It is also divided by the dot product of the plane normal and ray direction
	float t = -(plane.GetNormal().Dot(ray.GetOrigin()) + plane.GetDistance()) / planeRayDirection;
	
    //If the result of the equation is negative then there is no hit
    if (t < 0)
	{
		return false;
	}
	if (hitPoint)
	{
        //Here we calculate the point where the ray hits the plane
		Vector3 pointOnPlane = (ray.GetDirection() * t) + ray.GetOrigin();
		hitPoint->x = pointOnPlane.x;
		hitPoint->y = pointOnPlane.y;
		hitPoint->z = pointOnPlane.z;
	}
	return true;
}