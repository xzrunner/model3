// Copy from https://github.com/prideout/iphone-3d-programming

#include "m3_parametric_surface.h"
#include "m3_typedef.h"
#include "m3_model.h"

#include <ds_array.h>
#include <sm_const.h>

#include <string.h>
#include <stdbool.h>
#include <math.h>

struct parametric_interval {
//	struct sm_ivec2 slices;
	struct sm_ivec2 divisions;
	struct sm_vec2 upper_bound;
	struct sm_vec2 texture_count;
};

static inline struct sm_vec2
_compute_domain(const struct parametric_interval* pi, float x, float y) {
	struct sm_vec2 ret;
	ret.x = x * pi->upper_bound.x / (pi->divisions.x - 1);
	ret.y = y * pi->upper_bound.y / (pi->divisions.y - 1);
	return ret;
}

static struct ds_array*
_gen_vertices(const struct parametric_interval* pi, unsigned char flags, 
			  struct sm_vec3 (*evaluate)(struct sm_vec2* domain, const void* ud), const void* ud,
			  bool (*invert_normal)(struct sm_vec2* domain)) {
	int floats_per_vertex = 3;
	if (flags & M3_VERTEX_FLAG_NORMALS) {
		floats_per_vertex += 3;
	}
	if (flags & M3_VERTEX_FLAG_TEXCOORDS) {
		floats_per_vertex += 2;
	}

	int vertex_count = pi->divisions.x * pi->divisions.y;
	struct ds_array* vertices = ds_array_create(vertex_count, floats_per_vertex * sizeof(float));

	float vertex[floats_per_vertex];
	float* vertex_ptr = vertex;
	for (int y = 0; y < pi->divisions.y; ++y) {
		for (int x = 0; x < pi->divisions.x; ++x) {
			// Compute Position
			struct sm_vec2 domain = _compute_domain(pi, x, y);
			struct sm_vec3 range = evaluate(&domain, ud);
			memcpy(vertex_ptr, &range, sizeof(range));
			vertex_ptr += 3;
			// Compute Normal
			if (flags & M3_VERTEX_FLAG_NORMALS) {
				float s = x, t = y;
				// Nudge the point if the normal is indeterminate.
				if (x == 0) s += 0.01f;
				if (x == pi->divisions.x - 1) s -= 0.01f;
				if (y == 0) t += 0.01f;
				if (y == pi->divisions.y - 1) t -= 0.01f;
				// Compute the tangents and their cross product.
				struct sm_vec2 tmp = _compute_domain(pi, s, t);
				struct sm_vec3 p = evaluate(&tmp, ud);
				tmp = _compute_domain(pi, s + 0.01f, t);
				struct sm_vec3 u = evaluate(&tmp, ud);
				sm_vec3_vector(&u, &u, &p);
				tmp = _compute_domain(pi, s, t + 0.01f);
				struct sm_vec3 v = evaluate(&tmp, ud);
				sm_vec3_vector(&v, &v, &p);
				struct sm_vec3 normal;
				sm_vec3_cross(&normal, &u, &v);
				sm_vec3_normalize(&normal);
				if (invert_normal(&domain)) {
					normal.x = -normal.x;
					normal.y = -normal.y;
				}
				memcpy(vertex_ptr, &normal, sizeof(normal));
				vertex_ptr += 3;
			}
			// Compute Texcoords
			if (flags & M3_VERTEX_FLAG_TEXCOORDS) {
				float s = pi->texture_count.x * x / (pi->divisions.x - 1);
				float t = pi->texture_count.y * y / (pi->divisions.y - 1);
				memcpy(vertex_ptr, &s, sizeof(s));
				vertex_ptr += 1;
				memcpy(vertex_ptr, &t, sizeof(t));
				vertex_ptr += 1;
			}
			ds_array_add(vertices, vertex);
			vertex_ptr = vertex;
		}
	}

	return vertices;
}

static inline int
_get_triangle_index_count(const struct parametric_interval* pi) {
	return 6 * (pi->divisions.x - 1) * (pi->divisions.y - 1);
}

static struct ds_array*
_gen_triangle_indices(const struct parametric_interval* pi) {
	struct ds_array* indices = ds_array_create(_get_triangle_index_count(pi), sizeof(unsigned short));
	int slices_x = pi->divisions.x - 1,
		slices_y = pi->divisions.y - 1;
	int index;
	for (int y = 0, vertex = 0; y < slices_y; ++y) {
		for (int x = 0; x < slices_x; ++x) {
			int next = (x + 1) % pi->divisions.x;
			index = vertex + x;
			ds_array_add(indices, &index);
			index = vertex + next;
			ds_array_add(indices, &index);
			index = vertex + x + pi->divisions.x;
			ds_array_add(indices, &index);
			index = vertex + next;
			ds_array_add(indices, &index);
			index = vertex + next + pi->divisions.x;
			ds_array_add(indices, &index);
			index = vertex + x + pi->divisions.x;
			ds_array_add(indices, &index);
		}
		vertex += pi->divisions.x;
	}

	return indices;
}

//////////////////////////////////////////////////////////////////////////
// cone
//////////////////////////////////////////////////////////////////////////

struct cone {
	float height;
	float radius;
};

static struct sm_vec3
_cone_evaluate(struct sm_vec2* domain, const void* ud) {
	struct sm_vec3 ret;
	float u = domain->x, v = domain->y;
	const struct cone* cone = (const struct cone*)ud;
	ret.x = cone->radius * (1 - v) * cos(u);
	ret.y = cone->height * (v - 0.5f);
	ret.z = cone->radius * (1 - v) * -sin(u);
	return ret;
}

static bool 
_cone_invert_normal(struct sm_vec2* domain) {
	return false;
}

void 
m3_create_cone(float height, float radius, struct m3_mesh* mesh) {
	struct parametric_interval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = 1;
	pi.texture_count.x = 30;
	pi.texture_count.y = 20;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;

	struct cone cone = { height, radius };

	mesh->vertex_type = flags;

	mesh->vertices = _gen_vertices(&pi, flags, _cone_evaluate, &cone, _cone_invert_normal);

	mesh->indices = _gen_triangle_indices(&pi);
}

//////////////////////////////////////////////////////////////////////////
// Sphere
//////////////////////////////////////////////////////////////////////////

struct sphere {
	float radius;
};

static struct sm_vec3
_sphere_evaluate(struct sm_vec2* domain, const void* ud) {
	struct sm_vec3 ret;
	float u = domain->x, v = domain->y;
	const struct sphere* sphere = (const struct sphere*)ud;
	ret.x = sphere->radius * sin(u) * cos(v);
	ret.y = sphere->radius * cos(u);
	ret.z = sphere->radius * -sin(u) * sin(v);
	return ret;
}

static bool 
_sphere_invert_normal(struct sm_vec2* domain) {
	return false;
}

void 
m3_create_sphere(float radius, struct m3_mesh* mesh) {
	struct parametric_interval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 20;
	pi.texture_count.y = 35;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;

	struct sphere sphere = { radius };

	mesh->vertex_type = flags;

	mesh->vertices = _gen_vertices(&pi, flags, _sphere_evaluate, &sphere, _sphere_invert_normal);

	mesh->indices = _gen_triangle_indices(&pi);
}

//////////////////////////////////////////////////////////////////////////
// torus
//////////////////////////////////////////////////////////////////////////

struct torus {
	float major_radius;
	float minor_radius;
};

static struct sm_vec3
_torus_evaluate(struct sm_vec2* domain, const void* ud) {
	struct sm_vec3 ret;
	float u = domain->x, v = domain->y;
	const struct torus* torus = (const struct torus*)ud;
	const float major = torus->major_radius;
	const float minor = torus->minor_radius;
	ret.x = (major + minor * cos(v)) * cos(u);
	ret.y = (major + minor * cos(v)) * sin(u);
	ret.z = minor * sin(v);
	return ret;
}

static bool 
_torus_invert_normal(struct sm_vec2* domain) {
	return false;
}

void 
m3_create_torus(float major_radius, float minor_radius, struct m3_mesh* mesh) {
	struct parametric_interval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 40;
	pi.texture_count.y = 10;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;

	struct torus torus = { major_radius, minor_radius };

	mesh->vertex_type = flags;

	mesh->vertices = _gen_vertices(&pi, flags, _torus_evaluate, &torus, _torus_invert_normal);

	mesh->indices = _gen_triangle_indices(&pi);
}

//////////////////////////////////////////////////////////////////////////
// Trefoil Knot
//////////////////////////////////////////////////////////////////////////

struct trefoil_knot {
	float scale;
};

static struct sm_vec3
_trefoil_knot_evaluate(struct sm_vec2* domain, const void* ud) {
	struct sm_vec3 ret;

	const float a = 0.5f;
	const float b = 0.3f;
	const float c = 0.5f;
	const float d = 0.1f;
	float u = (SM_PI * 2 - domain->x) * 2;
	float v = domain->y;

	float r = a + b * cos(1.5f * u);
	float x = r * cos(u);
	float y = r * sin(u);
	float z = c * sin(1.5f * u);

	struct sm_vec3 dv;
	dv.x = -1.5f * b * sin(1.5f * u) * cos(u) - (a + b * cos(1.5f * u)) * sin(u);
	dv.y = -1.5f * b * sin(1.5f * u) * sin(u) + (a + b * cos(1.5f * u)) * cos(u);
	dv.z =  1.5f * c * cos(1.5f * u);

	struct sm_vec3 q = dv;
	sm_vec3_normalize(&q);
	struct sm_vec3 qvn = {q.y, -q.x, 0};
	sm_vec3_normalize(&qvn);
	struct sm_vec3 ww;
	sm_vec3_cross(&ww, &q, &qvn);

	ret.x = x + d * (qvn.x * cos(v) + ww.x * sin(v));
	ret.y = y + d * (qvn.y * cos(v) + ww.y * sin(v));
	ret.z = z + d * ww.z * sin(v);

	const struct trefoil_knot* tk = (const struct trefoil_knot*)ud;
	ret.x *= tk->scale;
	ret.y *= tk->scale;
	ret.z *= tk->scale;

	return ret;
}

static bool 
_trefoil_knot_invert_normal(struct sm_vec2* domain) {
	return false;
}

void 
m3_create_trefoil_knot(float scale, struct m3_mesh* mesh) {
	struct parametric_interval pi;
	pi.divisions.x = 60;
	pi.divisions.y = 15;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 100;
	pi.texture_count.y = 8;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;

	struct trefoil_knot tk = { scale };

	mesh->vertex_type = flags;

	mesh->vertices = _gen_vertices(&pi, flags, _trefoil_knot_evaluate, &tk, _trefoil_knot_invert_normal);

	mesh->indices = _gen_triangle_indices(&pi);
}

//////////////////////////////////////////////////////////////////////////
// Mobius Strip
//////////////////////////////////////////////////////////////////////////

struct mobius_strip {
	float scale;
};

static struct sm_vec3
_mobius_strip_evaluate(struct sm_vec2* domain, const void* ud) {
	struct sm_vec3 ret;

	float u = domain->x;
	float t = domain->y;
	float major = 1.25f;
	float a = 0.125f;
	float b = 0.5f;
	float phi = u / 2;

	// General equation for an ellipse where phi is the angle
	// between the major axis and the X axis.
	float x = a * cos(t) * cos(phi) - b * sin(t) * sin(phi);
	float y = a * cos(t) * sin(phi) + b * sin(t) * cos(phi);

	// Sweep the ellipse along a circle, like a torus.
	ret.x = (major + x) * cos(u);
	ret.y = (major + x) * sin(u);
	ret.z = y;

	const struct mobius_strip* ms = (const struct mobius_strip*)ud;
	ret.x *= ms->scale;
	ret.y *= ms->scale;
	ret.z *= ms->scale;

	return ret;
}

static bool 
_mobius_strip_invert_normal(struct sm_vec2* domain) {
	return false;
}

void 
m3_create_mobius_strip(float scale, struct m3_mesh* mesh) {
	struct parametric_interval pi;
	pi.divisions.x = 40;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 40;
	pi.texture_count.y = 15;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;

	struct mobius_strip ms = { scale };

	mesh->vertex_type = flags;

	mesh->vertices = _gen_vertices(&pi, flags, _mobius_strip_evaluate, &ms, _mobius_strip_invert_normal);

	mesh->indices = _gen_triangle_indices(&pi);
}

//////////////////////////////////////////////////////////////////////////
// Klein Bottle
//////////////////////////////////////////////////////////////////////////

struct klein_bottle {
	float scale;
};

static struct sm_vec3
_klein_bottle_evaluate(struct sm_vec2* domain, const void* ud) {
	struct sm_vec3 ret;

	float v = 1 - domain->x;
	float u = domain->y;

	float x0 = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(u) * cos(v);
	float y0 = 8 * sin(u) + (2 * (1 - cos(u) / 2)) * sin(u) * cos(v);

	float x1 = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(v + SM_PI);
	float y1 = 8 * sin(u);

	ret.x = u < SM_PI ? x0 : x1;
	ret.y = u < SM_PI ? -y0 : -y1;
	ret.z = (-2 * (1 - cos(u) / 2)) * sin(v);

	const struct klein_bottle* kb = (const struct klein_bottle*)ud;
	ret.x *= kb->scale;
	ret.y *= kb->scale;
	ret.z *= kb->scale;

	return ret;
}

static bool 
_klein_bottle_invert_normal(struct sm_vec2* domain) {
	return domain->y > 3 * SM_PI / 2;
}

void 
m3_create_klein_bottle(float scale, struct m3_mesh* mesh) {
	struct parametric_interval pi;
	pi.divisions.x = 20;
	pi.divisions.y = 20;
	pi.upper_bound.x = SM_PI * 2;
	pi.upper_bound.y = SM_PI * 2;
	pi.texture_count.x = 15;
	pi.texture_count.y = 50;

	unsigned char flags = M3_VERTEX_FLAG_NORMALS;

	struct klein_bottle ms = { scale };

	mesh->vertex_type = flags;

	mesh->vertices = _gen_vertices(&pi, flags, _klein_bottle_evaluate, &ms, _klein_bottle_invert_normal);

	mesh->indices = _gen_triangle_indices(&pi);
}