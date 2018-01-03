#include "node3/Mesh.h"

namespace n3
{

Mesh::Mesh()
	: m_vertex_type(0)
	, m_index_count(0)
{
}

Mesh::~Mesh()
{
}

void Mesh::SetRenderBuffer(int vertex_type, const CU_VEC<float>& vertices,
						   const CU_VEC<uint16_t>& indices)
{
	m_vertex_type = vertex_type;
	m_vertices = vertices;
	m_indices = indices;
}

}