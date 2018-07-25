#pragma once

#include <SM_Vector.h>
#include <SM_Quaternion.h>
#include <SM_Cube.h>
#include <SM_Matrix.h>

#include <vector>

namespace pt3 { class Ray; }

namespace n3
{

class Math
{
public:
	static bool RayAABBIntersection(const sm::cube& aabb, const pt3::Ray& ray, sm::vec3* coord);

	static bool RayOBBIntersection(const sm::cube& aabb, const sm::vec3& pos, const sm::Quaternion& angle,
		const sm::vec3& scale, const pt3::Ray& ray, sm::vec3* coord);

	static bool RayTriangleIntersection(const sm::mat4& mat, const sm::vec3& v0,
		const sm::vec3& v1, const sm::vec3& v2, const pt3::Ray& ray, sm::vec3* coord);
	static bool RayPolygonIntersection(const sm::mat4& mat, const std::vector<sm::vec3>& polygon,
		const pt3::Ray& ray, sm::vec3* coord);

}; // Math

}