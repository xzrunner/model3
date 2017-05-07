#include "c_wrap_m3.h"
#include "model3/ParametricEquations.h"
#include "model3/CameraQuat.h"
#include "model3/AssimpHelper.h"
#include "model3/AABB.h"
#include "model3/ModelParametric.h"

#include <SM_Vector.h>
#include <sm_c_vector.h>

namespace m3
{

/************************************************************************/
/* Surface                                                              */
/************************************************************************/

static m3::Model*
_create_model_from_surface(const m3::Surface* surface)
{
	m3::AABB aabb;
	m3::Model* model = new m3::ModelParametric(surface, aabb);
	return model;
}

extern "C"
void* m3_create_cone(float height, float radius)
{
	return _create_model_from_surface(new Cone(height, radius));
}

extern "C"
void* m3_create_sphere(float radius)
{
	return _create_model_from_surface(new Sphere(radius));
}

extern "C"
void* m3_create_torus(float major_radius, float minor_radius)
{
	return _create_model_from_surface(new Torus(major_radius, minor_radius));
}

extern "C"
void* m3_create_trefoi_knot(float scale)
{
	return _create_model_from_surface(new TrefoilKnot(scale));
}

extern "C"
void* m3_create_mobius_strip(float scale)
{
	return _create_model_from_surface(new MobiusStrip(scale));
}

extern "C"
void* m3_create_klein_bottle(float scale)
{
	return _create_model_from_surface(new KleinBottle(scale));
}

/************************************************************************/
/* Model                                                                */
/************************************************************************/

extern "C"
void* m3_create_model(const char* filepath)
{
	return AssimpHelper::Load(filepath);
}

/************************************************************************/
/* camera                                                               */
/************************************************************************/

extern "C"
void* m3_cam_create()
{
	return new CameraQuat;
}

extern "C"
void m3_cam_release(void* cam)
{
	CameraQuat* c = static_cast<CameraQuat*>(cam);
	delete c;
}

extern "C"
void m3_cam_rotate(void* cam, const struct sm_vec3* b, const struct sm_vec3* e)
{
	CameraQuat* c = static_cast<CameraQuat*>(cam);

	sm::vec3 begin(b->x, b->y, b->z), end(e->x, e->y, e->z);
	c->Rotate(begin, end);
}

extern "C"
void m3_cam_translate(void* cam, float x, float y, float z)
{
	CameraQuat* c = static_cast<CameraQuat*>(cam);
	c->Translate(sm::vec3(x, y, z));
}

extern "C"
void  m3_cam_get_mat(const void* cam, float mat[16])
{
	const CameraQuat* c = static_cast<const CameraQuat*>(cam);
	sm::mat4 mt = c->ToMat();
	memcpy(mat, mt.x, sizeof(mt.x));
}

}