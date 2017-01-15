#ifndef _MODEL3_PARAMETRIC_SURFACE_H_
#define _MODEL3_PARAMETRIC_SURFACE_H_

#include <SM_Vector.h>

namespace m3
{

class Mesh;

class ParametricSurface
{
public:
	virtual ~ParametricSurface() {}
	virtual Mesh* CreateMesh() const = 0;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const = 0;
	virtual bool InvertNormal(const sm::vec2& domain) const { return false; }
}; // ParametricSurface

class Cone : public ParametricSurface
{
public:
	Cone(float height, float radius);

	virtual Mesh* CreateMesh() const;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const;

private:
	float m_height;
	float m_radius;

}; // Cone

class Sphere : public ParametricSurface
{
public:
	Sphere(float radius);

	virtual Mesh* CreateMesh() const;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const;

private:
	float m_radius;

}; // Sphere

class Torus : public ParametricSurface
{
public:
	Torus(float major_radius, float minor_radius);

	virtual Mesh* CreateMesh() const;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const;

private:
	float m_major_radius;
	float m_minor_radius;

}; // Torus

class TrefoilKnot : public ParametricSurface
{
public:
	TrefoilKnot(float scale);

	virtual Mesh* CreateMesh() const;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const;

private:
	float m_scale;

}; // TrefoilKnot

class MobiusStrip : public ParametricSurface
{
public:
	MobiusStrip(float scale);

	virtual Mesh* CreateMesh() const;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const;

private:
	float m_scale;

}; // MobiusStrip

class KleinBottle : public ParametricSurface
{
public:
	KleinBottle(float scale);

	virtual Mesh* CreateMesh() const;
	virtual sm::vec3 Evaluate(const sm::vec2& domain) const;
	virtual bool InvertNormal(const sm::vec2& domain) const;

private:
	float m_scale;

}; // KleinBottle

class ParametricInterval 
{
public:
	//	sm::ivec2 slices;
	sm::ivec2 divisions;
	sm::vec2  upper_bound;
	sm::vec2  texture_count;

public:
	sm::vec2 CalcDomain(float x, float y) const;
	int CalcTriangleIndexCount() const;

	void GenVertices(const ParametricSurface& surface, Mesh& mesh) const;
	void GenIndices(Mesh& mesh) const;

}; // ParametricInterval

}

#endif // _MODEL3_PARAMETRIC_SURFACE_H_