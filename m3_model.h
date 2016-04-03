#ifdef __cplusplus
extern "C"
{
#endif

#ifndef model3_model_h
#define model3_model_h

#include "m3_material.h"

struct ds_array;

struct m3_mesh {
	int vertex_type;

	struct ds_array* vertices;
	struct ds_array* indices;

	struct m3_material material;
};

struct m3_model {
	struct ds_array* meshes;
};

struct m3_model* m3_model_create(int mesh_cap);
void m3_model_release(struct m3_model*);

#endif // model3_model_h

#ifdef __cplusplus
}
#endif