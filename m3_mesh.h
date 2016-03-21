#ifdef __cplusplus
extern "C"
{
#endif

#ifndef model3_mesh_h
#define model3_mesh_h

struct ds_array;

struct m3_mesh {
	struct ds_array* vertices;
	struct ds_array* indices;
};

#endif // model3_mesh_h

#ifdef __cplusplus
}
#endif