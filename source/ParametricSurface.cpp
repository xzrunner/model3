#include "ParametricSurface.h"
#include "m3_typedef.h"
#include "Mesh.h"

#include <sm_const.h>

namespace m3
{

/************************************************************************/
/* class Cone                                                           */
/************************************************************************/

Cone::Cone(float height, float radius)
	: m_height(height)
	, m_radius(radius)
{

}

Mesh* Cone::CreateMesh() const
{
	Mesh* mesh = new Mesh;

	ParametricInterval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = 1;
	pi.texture_count.x = 30;
	pi.texture_count.y = 20;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;
	mesh->vertex_type = flags;

	pi.GenVertices(*this, *mesh);
	pi.GenIndices(*mesh);

	return mesh;
}

sm::vec3 Cone::Evaluate(const sm::vec2& domain) const
{
	sm::vec3 ret;
	float u = domain.x, v = domain.y;
	ret.x = m_radius * (1 - v) * cos(u);
	ret.y = m_height * (v - 0.5f);
	ret.z = m_radius * (1 - v) * -sin(u);
	return ret;
}

/************************************************************************/
/* class Sphere                                                         */
/************************************************************************/

Sphere::Sphere(float radius)
	: m_radius(radius)
{
}

Mesh* Sphere::CreateMesh() const
{
	Mesh* mesh = new Mesh;

	ParametricInterval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 20;
	pi.texture_count.y = 35;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;
	mesh->vertex_type = flags;

	pi.GenVertices(*this, *mesh);
	pi.GenIndices(*mesh);

	return mesh;
}

sm::vec3 Sphere::Evaluate(const sm::vec2& domain) const
{
	sm::vec3 ret;
	float u = domain.x, v = domain.y;
	ret.x = m_radius * sin(u) * cos(v);
	ret.y = m_radius * cos(u);
	ret.z = m_radius * -sin(u) * sin(v);
	return ret;
}

/************************************************************************/
/* class Torus                                                          */
/************************************************************************/

Torus::Torus(float major_radius, float minor_radius)
	: m_major_radius(m_major_radius)
	, m_minor_radius(minor_radius)
{
}

Mesh* Torus::CreateMesh() const
{
	Mesh* mesh = new Mesh;

	ParametricInterval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 40;
	pi.texture_count.y = 10;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;
	mesh->vertex_type = flags;

	pi.GenVertices(*this, *mesh);
	pi.GenIndices(*mesh);

	return mesh;
}

sm::vec3 Torus::Evaluate(const sm::vec2& domain) const
{
	sm::vec3 ret;
	float u = domain.x, v = domain.y;
	const float major = m_major_radius;
	const float minor = m_minor_radius;
	ret.x = (major + minor * cos(v)) * cos(u);
	ret.y = (major + minor * cos(v)) * sin(u);
	ret.z = minor * sin(v);
	return ret;
}

/************************************************************************/
/* class TrefoilKnot                                                    */
/************************************************************************/

TrefoilKnot::TrefoilKnot(float scale)
	: m_scale(scale)
{
}

Mesh* TrefoilKnot::CreateMesh() const
{
	Mesh* mesh = new Mesh;

	ParametricInterval pi;
	pi.divisions.x = 60;
	pi.divisions.y = 15;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 100;
	pi.texture_count.y = 8;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;
	mesh->vertex_type = flags;

	pi.GenVertices(*this, *mesh);
	pi.GenIndices(*mesh);

	return mesh;
}

sm::vec3 TrefoilKnot::Evaluate(const sm::vec2& domain) const
{
	sm::vec3 ret;

	const float a = 0.5f;
	const float b = 0.3f;
	const float c = 0.5f;
	const float d = 0.1f;
	float u = (SM_PI * 2 - domain.x) * 2;
	float v = domain.y;

	float r = a + b * cos(1.5f * u);
	float x = r * cos(u);
	float y = r * sin(u);
	float z = c * sin(1.5f * u);

	sm::vec3 dv;
	dv.x = -1.5f * b * sin(1.5f * u) * cos(u) - (a + b * cos(1.5f * u)) * sin(u);
	dv.y = -1.5f * b * sin(1.5f * u) * sin(u) + (a + b * cos(1.5f * u)) * cos(u);
	dv.z =  1.5f * c * cos(1.5f * u);

	sm::vec3 q = dv.Normalized();
	sm::vec3 qvn(q.y, -q.x, 0);
	qvn.Normalize();
	sm::vec3 ww = q.Cross(qvn);

	ret.x = x + d * (qvn.x * cos(v) + ww.x * sin(v));
	ret.y = y + d * (qvn.y * cos(v) + ww.y * sin(v));
	ret.z = z + d * ww.z * sin(v);

	ret *= m_scale;

	return ret;
}

/************************************************************************/
/* class MobiusStrip                                                    */
/************************************************************************/

MobiusStrip::MobiusStrip(float scale)
	: m_scale(scale)
{
}

Mesh* MobiusStrip::CreateMesh() const
{
	Mesh* mesh = new Mesh;

	ParametricInterval pi;
	pi.divisions.x = 40;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 40;
	pi.texture_count.y = 15;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;
	mesh->vertex_type = flags;

	pi.GenVertices(*this, *mesh);
	pi.GenIndices(*mesh);

	return mesh;
}

sm::vec3 MobiusStrip::Evaluate(const sm::vec2& domain) const
{
	sm::vec3 ret;

	float u = domain.x;
	float t = domain.y;
	float major = 1.25f;
	float a = 0.125f;
	float b = 0.5f;
	float phi = u / 2;

	// General equation for an ellipse where phi is the angle
	// between the major axis and the X axis.
	float x = a * cos(t) * cos(phi) - b * sin(t) * sin(phi);
	float y = a * cos(t) * sin(phi) + b * sin(t) * cos(phi);

	// Sweep the ellipse along a circle, like a torus.
	ret.x = (major + x) * cos(u);
	ret.y = (major + x) * sin(u);
	ret.z = y;

	ret *= m_scale;

	return ret;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

KleinBottle::KleinBottle(float scale)
	: m_scale(scale)
{
}

Mesh* KleinBottle::CreateMesh() const
{
	Mesh* mesh = new Mesh;

	ParametricInterval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 15;
	pi.texture_count.y = 50;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;
	mesh->vertex_type = flags;

	pi.GenVertices(*this, *mesh);
	pi.GenIndices(*mesh);

	return mesh;
}

sm::vec3 KleinBottle::Evaluate(const sm::vec2& domain) const
{
	sm::vec3 ret;

	float v = 1 - domain.x;
	float u = domain.y;

	float x0 = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(u) * cos(v);
	float y0 = 8 * sin(u) + (2 * (1 - cos(u) / 2)) * sin(u) * cos(v);

	float x1 = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(v + SM_PI);
	float y1 = 8 * sin(u);

	ret.x = u < SM_PI ? x0 : x1;
	ret.y = u < SM_PI ? -y0 : -y1;
	ret.z = (-2 * (1 - cos(u) / 2)) * sin(v);

	ret *= m_scale;

	return ret;
}

bool KleinBottle::InvertNormal(const sm::vec2& domain) const
{
	return domain.y > 3 * SM_PI / 2;
}

/************************************************************************/
/* class ParametricInterval                                             */
/************************************************************************/

sm::vec2 ParametricInterval::CalcDomain(float x, float y) const
{
	sm::vec2 ret;
	ret.x = x * upper_bound.x / (divisions.x - 1);
	ret.y = y * upper_bound.y / (divisions.y - 1);
	return ret;
}

int ParametricInterval::CalcTriangleIndexCount() const
{
	return 6 * (divisions.x - 1) * (divisions.y - 1);
}

void ParametricInterval::GenVertices(const ParametricSurface& surface, Mesh& mesh) const
{
	int vertex_count = divisions.x * divisions.y;
	mesh.vertices.reserve(vertex_count);
	if (mesh.vertex_type & M3_VERTEX_FLAG_TEXCOORDS) {
		mesh.texcoords.reserve(vertex_count);
	}
	if (mesh.vertex_type & M3_VERTEX_FLAG_NORMALS) {
		mesh.normals.reserve(vertex_count);
	}

	for (int y = 0; y < divisions.y; ++y) 
	{
		for (int x = 0; x < divisions.x; ++x) 
		{
			// Compute Position
			sm::vec2 domain = CalcDomain(static_cast<float>(x), static_cast<float>(y));
			mesh.vertices.push_back(surface.Evaluate(domain));
			// Compute Normal
			if (mesh.vertex_type & M3_VERTEX_FLAG_NORMALS) 
			{
				float s = static_cast<float>(x), t = static_cast<float>(y);
				// Nudge the point if the normal is indeterminate.
				if (x == 0) s += 0.01f;
				if (x == divisions.x - 1) s -= 0.01f;
				if (y == 0) t += 0.01f;
				if (y == divisions.y - 1) t -= 0.01f;
				// Compute the tangents and their cross product.
				sm::vec2 tmp = CalcDomain(s, t);
				sm::vec3 p = surface.Evaluate(tmp);
				tmp = CalcDomain(s + 0.01f, t);
				sm::vec3 u = surface.Evaluate(tmp) - p;
				tmp = CalcDomain(s, t + 0.01f);
				sm::vec3 v = surface.Evaluate(tmp) - p;
				sm::vec3 normal = u.Cross(v).Normalized();
				if (surface.InvertNormal(domain)) {
					normal.x = -normal.x;
					normal.y = -normal.y;
				}
				mesh.normals.push_back(normal);
			}
			// Compute Texcoords
			if (mesh.vertex_type & M3_VERTEX_FLAG_TEXCOORDS) 
			{
				float s = texture_count.x * x / (divisions.x - 1);
				float t = texture_count.y * y / (divisions.y - 1);
				mesh.texcoords.push_back(sm::vec2(s, t));
			}
		}
	}
}

void ParametricInterval::GenIndices(Mesh& mesh) const
{
	int count = CalcTriangleIndexCount();
	mesh.indices.reserve(count);
	int slices_x = divisions.x - 1,
		slices_y = divisions.y - 1;
	int index;
	for (int y = 0, vertex = 0; y < slices_y; ++y) 
	{
		for (int x = 0; x < slices_x; ++x) 
		{
			int next = (x + 1) % divisions.x;
			index = vertex + x;
			mesh.indices.push_back(index);
			index = vertex + next;
			mesh.indices.push_back(index);
			index = vertex + x + divisions.x;
			mesh.indices.push_back(index);
			index = vertex + next;
			mesh.indices.push_back(index);
			index = vertex + next + divisions.x;
			mesh.indices.push_back(index);
			index = vertex + x + divisions.x;
			mesh.indices.push_back(index);
		}
		vertex += divisions.x;
	}
}

}