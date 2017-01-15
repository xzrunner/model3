#include "ModelParametric.h"
#include "ParametricSurface.h"
#include "AABB.h"

#include <unirender/RenderContext.h>
#include <shaderlab/ShaderMgr.h>
#include <shaderlab/Buffer.h>
#include <shaderlab/RenderBuffer.h>

namespace m3
{

ModelParametric::ModelParametric()
{

}

ModelParametric::ModelParametric(const Surface* surface, AABB& aabb)
{
	Mesh mesh;

	unsigned char flags = VertexFlagsNormals;

	int stride = 3;
	if (flags & VertexFlagsNormals) {
		stride += 3;
	}
	if (flags & VertexFlagsTexCoords) {
		stride += 2;
	}

	ur::RenderContext* rc = sl::ShaderMgr::Instance()->GetContext();

	// Create the VBO for the vertices.
	std::vector<float> vertices;
	surface->GenerateVertices(vertices, flags);
	int vertex_count = surface->GetVertexCount();
	sl::Buffer* vertices_buf = new sl::Buffer(stride, vertex_count);
	vertices_buf->Add(&vertices[0], vertex_count);
	sl::RenderBuffer* vb = new sl::RenderBuffer(rc, ur::VERTEXBUFFER, stride, vertex_count, vertices_buf);
	
	// Create a new VBO for the indices if needed.
	int index_count = surface->GetTriangleIndexCount();
	std::vector<unsigned short> indices(index_count);
	surface->GenerateTriangleIndices(indices);
	sl::Buffer* indices_buf = new sl::Buffer(sizeof(uint16_t), index_count);
	indices_buf->Add(&indices[0], index_count);
	sl::RenderBuffer* ib = new sl::RenderBuffer(rc, ur::INDEXBUFFER, sizeof(uint16_t), index_count, indices_buf);

	mesh.SetRenderBuffer(vb, ib);
	vb->RemoveReference();
	ib->RemoveReference();

	mesh.SetIndexCount(surface->GetTriangleIndexCount());

	m_meshes.push_back(mesh);

	// Init aabb
	for (int i = 0, n = vertices.size(); i < n; )
	{
		sm::vec3 pos;
		pos.x = vertices[i];
		pos.y = vertices[i+1];
		pos.z = vertices[i+2];
		aabb.Combine(pos);
		i += stride;
	}
}

}