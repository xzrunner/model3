#pragma once

#include <SM_Vector.h>
#include <SM_Quaternion.h>

namespace pt3 { class AABB; class Ray; }

namespace n3
{

class Math
{
public:
	static bool RayAABBIntersection(const pt3::AABB& aabb, const pt3::Ray& ray, sm::vec3* coord);

	static bool RayOBBIntersection(const pt3::AABB& aabb, const sm::vec3& pos, const sm::Quaternion& angle,
		const sm::vec3& scale, const pt3::Ray& ray, sm::vec3* coord);

}; // Math

}