#ifdef __cplusplus
extern "C"
{
#endif

#ifndef model3_material_h
#define model3_material_h

#include "sm_math.h"

struct m3_material {
	sm_vec3 ambient;
	sm_vec3 diffuse;
	sm_vec3 specular;
};

#endif // model3_material_h

#ifdef __cplusplus
}
#endif