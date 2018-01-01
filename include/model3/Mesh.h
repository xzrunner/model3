#ifndef _MODEL3_MESH_H_
#define _MODEL3_MESH_H_

#include <cu/CU_RefCountObj.h>
#include <cu/uncopyable.h>
#include <cu/cu_stl.h>

#include "Material.h"

#include <stdint.h>

namespace m3
{

class Mesh : public cu::RefCountObj, private cu::Uncopyable
{
public:
	Mesh();
	virtual ~Mesh();

	void SetRenderBuffer(int vertex_type, const CU_VEC<float>& vertices,
		const CU_VEC<uint16_t>& indices);

	void SetIndexCount(int count) { m_index_count = count; }

	void SetMaterial(const Material& material) { m_material = material; }
	const Material& GetMaterial() const { return m_material; }

	int GetVertexType() const { return m_vertex_type; }
	const CU_VEC<float>& GetVertices() const { return m_vertices; }

	const CU_VEC<uint16_t>& GetIndices() const { return m_indices; }

private:
	int m_vertex_type;
	CU_VEC<float> m_vertices;

	CU_VEC<uint16_t> m_indices;

	int m_index_count;

	Material m_material;

}; // Mesh

}

#endif // _MODEL3_MESH_H_