#include "m3_model.h"

#include <ds_array.h>

#include <stdlib.h>

struct m3_model* 
m3_model_create(int mesh_cap) {
	struct m3_model* model = malloc(sizeof(*model));
	model->meshes = ds_array_create(mesh_cap, sizeof(struct m3_mesh*));
	return model;
}

void 
m3_model_release(struct m3_model* model) {
	for (int i = 0, n = ds_array_size(model->meshes); i < n; ++i) {
		struct m3_mesh* mesh = (struct m3_mesh*)ds_array_fetch(model->meshes, i);
		free(mesh);
	}
	free(model);
}