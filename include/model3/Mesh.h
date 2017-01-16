#ifndef _MODEL3_MESH_H_
#define _MODEL3_MESH_H_

#include <CU_RefCountObj.h>
#include <CU_Uncopyable.h>

#include "Material.h"

#include <vector>

#include <stdint.h>

namespace m3
{

class Mesh : public cu::RefCountObj, private cu::Uncopyable
{
public:
	Mesh();
	virtual ~Mesh();

	void SetRenderBuffer(int vertex_type, const std::vector<float>& vertices,
		const std::vector<uint16_t>& indices);

	void SetIndexCount(int count) { m_index_count = count; }

	void SetMaterial(const Material& material) { m_material = material; }

	int GetVertexType() const { return m_vertex_type; }
	const std::vector<float>& GetVertices() const { return m_vertices; }

	const std::vector<uint16_t>& GetIndices() const { return m_indices; }

private:
	int m_vertex_type;
	std::vector<float> m_vertices;

	std::vector<uint16_t> m_indices; 

	int m_index_count;

	Material m_material;

}; // Mesh

}

#endif // _MODEL3_MESH_H_