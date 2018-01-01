#pragma once

#include <SM_Vector.h>
#include <SM_Quaternion.h>

namespace m3
{

class AABB;
class Ray;

class Math
{
public:
	static bool RayAABBIntersection(const AABB& aabb, const Ray& ray, sm::vec3* coord);

	static bool RayOBBIntersection(const AABB& aabb, const sm::vec3& pos, const sm::Quaternion& angle,
		const Ray& ray, sm::vec3* coord);

}; // Math

}