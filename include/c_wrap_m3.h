#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _m3_wrap_c_h_
#define _m3_wrap_c_h_

void* m3_create_cone(float height, float radius);
void* m3_create_sphere(float radius);
void* m3_create_torus(float major_radius, float minor_radius);
void* m3_create_trefoi_knot(float scale);
void* m3_create_mobius_strip(float scale);
void* m3_create_klein_bottle(float scale);

#endif // _m3_wrap_c_h_

#ifdef __cplusplus
}
#endif