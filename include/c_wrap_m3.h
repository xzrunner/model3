#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _m3_wrap_c_h_
#define _m3_wrap_c_h_

/************************************************************************/
/* Surface                                                              */
/************************************************************************/

void* m3_create_cone(float height, float radius);
void* m3_create_sphere(float radius);
void* m3_create_torus(float major_radius, float minor_radius);
void* m3_create_trefoi_knot(float scale);
void* m3_create_mobius_strip(float scale);
void* m3_create_klein_bottle(float scale);

/************************************************************************/
/* Model                                                                */
/************************************************************************/

void* m3_create_model(const char* filepath);

/************************************************************************/
/* camera                                                               */
/************************************************************************/

void* m3_cam_create();
void  m3_cam_release(void* cam);
void  m3_cam_rotate(void* cam, const struct sm_vec3* begin, const struct sm_vec3* end);
void  m3_cam_translate(void* cam, float x, float y, float z);
void  m3_cam_get_mat(const void* cam, float mat[16]);

#endif // _m3_wrap_c_h_

#ifdef __cplusplus
}
#endif