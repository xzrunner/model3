#include "c_wrap_m3.h"
#include "model3/ParametricEquations.h"

namespace m3
{

extern "C"
void* m3_create_cone(float height, float radius)
{
	return new Cone(height, radius);
}

extern "C"
void* m3_create_sphere(float radius)
{
	return new Sphere(radius);
}

extern "C"
void* m3_create_torus(float major_radius, float minor_radius)
{
	return new Torus(major_radius, minor_radius);
}

extern "C"
void* m3_create_trefoi_knot(float scale)
{
	return new TrefoilKnot(scale);
}

extern "C"
void* m3_create_mobius_strip(float scale)
{
	return new MobiusStrip(scale);
}

extern "C"
void* m3_create_klein_bottle(float scale)
{
	return new KleinBottle(scale);
}

}