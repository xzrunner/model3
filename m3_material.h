#ifdef __cplusplus
extern "C"
{
#endif

#ifndef model3_material_h
#define model3_material_h

#include "m3_math.h"

struct m3_material {
	m3_vec3 ambient;
	m3_vec3 diffuse;
	m3_vec3 specular;
};

#endif // model3_material_h

#ifdef __cplusplus
}
#endif