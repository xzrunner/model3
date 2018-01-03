#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _n3_wrap_c_h_
#define _n3_wrap_c_h_

/************************************************************************/
/* Surface                                                              */
/************************************************************************/

void* n3_create_cone(float height, float radius);
void* n3_create_sphere(float radius);
void* n3_create_torus(float major_radius, float minor_radius);
void* n3_create_trefoi_knot(float scale);
void* n3_create_mobius_strip(float scale);
void* n3_create_klein_bottle(float scale);

/************************************************************************/
/* Model                                                                */
/************************************************************************/

void* n3_create_model(const char* filepath);

/************************************************************************/
/* camera                                                               */
/************************************************************************/

void* n3_cam_create();
void  n3_cam_release(void* cam);
void  n3_cam_rotate(void* cam, const struct sm_vec3* begin, const struct sm_vec3* end);
void  n3_cam_translate(void* cam, float x, float y, float z);
void  n3_cam_get_mat(const void* cam, float mat[16]);

#endif // _n3_wrap_c_h_

#ifdef __cplusplus
}
#endif