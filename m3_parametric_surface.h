#ifdef __cplusplus
extern "C"
{
#endif

#ifndef model3_parametric_surface_h
#define model3_parametric_surface_h

struct m3_mesh;

void m3_create_cone(float height, float radius, struct m3_mesh*);
void m3_create_sphere(float radius, struct m3_mesh*);
void m3_create_torus(float major_radius, float minor_radius, struct m3_mesh*);
void m3_create_trefoil_knot(float scale, struct m3_mesh*);
void m3_create_mobius_strip(float scale, struct m3_mesh*);
void m3_create_klein_bottle(float scale, struct m3_mesh*);

#endif // model3_parametric_surface_h

#ifdef __cplusplus
}
#endif