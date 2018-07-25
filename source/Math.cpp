#include "node3/Math.h"

#include <SM_Matrix.h>
#include <painting3/AABB.h>
#include <painting3/Ray.h>

namespace n3
{

#define NUMDIM	3
#define RIGHT	0
#define LEFT	1
#define MIDDLE	2

// This code from GraphicsGems's RayBox.c
// https://github.com/erich666/GraphicsGems/blob/master/gems/RayBox.c
bool Math::RayAABBIntersection(const pt3::AABB& aabb, const pt3::Ray& ray, sm::vec3* coord)
{
	sm::vec3 cross;

	char quadrant[3];
	float candidate_plane[3];
	bool inside = true;

	/* Find candidate planes; this loop can be avoided if
   	rays cast all from the eye(assume perpsective view) */
	for (int i = 0; i < 3; ++i)
	{
		if (ray.Start()[i] < aabb.Min()[i]) {
			quadrant[i] = LEFT;
			candidate_plane[i] = aabb.Min()[i];
			inside = false;
		} else if (ray.Start()[i] > aabb.Max()[i]) {
			quadrant[i] = RIGHT;
			candidate_plane[i] = aabb.Max()[i];
			inside = false;
		} else {
			quadrant[i] = MIDDLE;
		}
	}

	/* pt3::Ray origin inside bounding box */
	if (inside) {
		cross = ray.Start();
		return true;
	}

	float max_t[3];
	/* Calculate T distances to candidate planes */
	for (int i = 0; i < 3; ++i) {
		if (quadrant[i] != MIDDLE && ray.Dir()[i] != 0) {
			max_t[i] = (candidate_plane[i]-ray.Start()[i])/ray.Dir()[i];
		} else {
			max_t[i] = -1;
		}
	}

	/* Get largest of the maxT's for final choice of intersection */
	int which_plane = 0;
	for (int i = 1; i < 3; ++i) {
		if (max_t[which_plane] < max_t[i]) {
			which_plane = i;
		}
	}

	/* Check final candidate actually inside box */
	if (max_t[which_plane] < 0) {
		return false;
	}
	for (int i = 0; i < 3; ++i) {
		if (which_plane != i) {
			cross[i] = ray.Start()[i] + max_t[which_plane] * ray.Dir()[i];
			if (cross[i] < aabb.Min()[i] || cross[i] > aabb.Max()[i]) {
				return false;
			}
		} else {
			cross[i] = candidate_plane[i];
		}
	}

	if (coord) {
		*coord = cross;
	}

	return true;
}

bool Math::RayOBBIntersection(const pt3::AABB& aabb, const sm::vec3& pos, const sm::Quaternion& angle,
	                          const sm::vec3& scale, const pt3::Ray& ray, sm::vec3* coord)
{
	sm::mat4 rot_mat(-angle);

	sm::vec3 start = rot_mat * (ray.Start() - pos);
	sm::vec3 dir = rot_mat * ray.Dir();
	pt3::Ray ray_fix(start, dir);

	auto aabb_scaled = aabb;
	aabb_scaled.Scale(scale);

	return RayAABBIntersection(aabb_scaled, ray_fix, coord);
}

// Code from glm/gtx/intersect.h intersectRayTriangle
bool Math::RayTriangleIntersection(const sm::mat4& mat, const sm::vec3& v0, const sm::vec3& v1,
	                               const sm::vec3& v2, const pt3::Ray& ray, sm::vec3* coord)
{
	auto _v0 = mat * v0;
	// fixme
	//auto _v1 = mat * v1;
	//auto _v2 = mat * v2;
	auto _v1 = mat * v2;
	auto _v2 = mat * v1;

	auto e1 = _v1 - _v0;
	auto e2 = _v2 - _v0;

	auto p = ray.Dir().Cross(e2);;
	auto a = e1.Dot(p);

	auto epsilon = std::numeric_limits<float>::epsilon();
	if (a < epsilon) {
		return false;
	}

	float f = 1.0f / a;

	auto s = ray.Start() - _v0;
	coord->x = f * s.Dot(p);
	if (coord->x < 0.0f) {
		return false;
	}
	if (coord->x > 1.0f) {
		return false;
	}

	auto q = s.Cross(e1);
	coord->y = f * ray.Dir().Dot(q);
	if (coord->y < 0.0f) {
		return false;
	}
	if (coord->y + coord->x > 1.0f) {
		return false;
	}

	coord->z = f * e2.Dot(q);

	return coord->z >= 0.0f;
}

bool Math::RayPolygonIntersection(const sm::mat4& mat, const std::vector<sm::vec3>& polygon,
	                              const pt3::Ray& ray, sm::vec3* coord)
{
	for (int i = 1, n = polygon.size(); i < n - 1; ++i) {
		if (RayTriangleIntersection(mat, polygon[0], polygon[i], polygon[i + 1], ray, coord)) {
			return true;
		}
	}
	return false;
}

}