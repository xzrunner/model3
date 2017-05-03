#include "model3/ModelParametric.h"
#include "model3/ParametricSurface.h"
#include "model3/AABB.h"
#include "model3/Mesh.h"
#include "model3/m3_typedef.h"

namespace m3
{

ModelParametric::ModelParametric()
{

}

ModelParametric::ModelParametric(const Surface* surface, AABB& aabb)
{
	Mesh* mesh = new Mesh;

	int vertex_type = VERTEX_FLAG_NORMALS;

	int stride = 3;
	if (vertex_type & VERTEX_FLAG_NORMALS) {
		stride += 3;
	}
	if (vertex_type & VERTEX_FLAG_TEXCOORDS) {
		stride += 2;
	}

	// Create the VBO for the vertices.
	std::vector<float> vertices;
	surface->GenerateVertices(vertex_type, vertices);
	int vertex_count = surface->GetVertexCount();
	
	// Create a new VBO for the indices if needed.
	int index_count = surface->GetTriangleIndexCount();
	std::vector<unsigned short> indices(index_count);
	surface->GenerateTriangleIndices(indices);

	mesh->SetRenderBuffer(vertex_type, vertices, indices);
	mesh->SetIndexCount(surface->GetTriangleIndexCount());

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