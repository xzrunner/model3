#ifndef _MODEL3_MESH_H_
#define _MODEL3_MESH_H_

#include "Material.h"

#include <vector>

#include <stdint.h>

namespace sl { class RenderBuffer; class RenderLayout; }

namespace m3
{

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void SetRenderBuffer(sl::RenderBuffer* vb, sl::RenderBuffer* ib);

	void SetIndexCount(int count) { m_index_count = count; }

	void SetMaterial(const sm::vec3& ambient, const sm::vec3& diffuse, const sm::vec3& specular);

private:
	sl::RenderBuffer *m_vb, *m_ib;
	sl::RenderLayout* m_layout;

	int m_index_count;

	Material m_material;

}; // Mesh

}

#endif // _MODEL3_MESH_H_