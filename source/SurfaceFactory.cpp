#include "node3/SurfaceFactory.h"
#include "node3/ParametricEquations.h"

namespace n3
{

Surface* SurfaceFactory::Create(const std::string& name)
{
	Surface* surface = nullptr;
	if (name == "Cone") {
		surface = new Cone(2, 1);
	}  else if (name == "Sphere") {
		surface = new Sphere(1);
	} else if (name == "Torus") {
		surface = new Torus(0.5f, 0.2f);
	} else if (name == "TrefoilKnot") {
		surface = new TrefoilKnot(1);
	} else if (name == "MobiusStrip") {
		surface = new MobiusStrip(0.2f);
	} else if (name == "KleinBottle") {
		surface = new KleinBottle(0.1f);
	}
	return surface;
}

}