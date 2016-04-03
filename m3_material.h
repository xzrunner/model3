#ifdef __cplusplus
extern "C"
{
#endif

#ifndef model3_material_h
#define model3_material_h

#include "sm_vector.h"

struct m3_material {
	struct sm_vec3 ambient;
	struct sm_vec3 diffuse;
	struct sm_vec3 specular;
	float shininess;
	int tex;
};

#endif // model3_material_h

#ifdef __cplusplus
}
#endif