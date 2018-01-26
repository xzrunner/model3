#include "node3/ModelParametric.h"
#include "node3/ParametricSurface.h"
#include "node3/AABB.h"
#include "node3/Mesh.h"
#include "node3/n3_typedef.h"
#include "node3/SurfaceFactory.h"

namespace n3
{

const char* const ModelParametric::TYPE_NAME = "parametric";

ModelParametric::ModelParametric()
{
}

ModelParametric::ModelParametric(const Surface* surface, AABB& aabb)
{
	m_meshes.push_back(CreateMeshFromSurface(surface, aabb));
}

bool ModelParametric::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
//	val.SetObject();

	rapidjson::Value val_meshes;
	val_meshes.SetArray();
	for (auto& mesh : m_meshes) {
		rapidjson::Value val_mesh;
		val_mesh.SetString(mesh->GetType().c_str(), alloc);
		val_meshes.PushBack(val_mesh, alloc);
	}

	val.AddMember("meshes", val_meshes, alloc);

	return true;
}

void ModelParametric::LoadFromJson(const rapidjson::Value& val)
{
	if (!val.HasMember("meshes")) {
		return;
	}

	AABB aabb;
	for (auto& val_mesh : val["meshes"].GetArray()) {
		auto surface = SurfaceFactory::Create(val_mesh.GetString());
		m_meshes.push_back(CreateMeshFromSurface(surface, aabb));
	}
}

MeshPtr ModelParametric::CreateMeshFromSurface(const Surface* surface, AABB& aabb)
{
	auto mesh = std::make_shared<Mesh>();

	mesh->SetType(surface->Type());

	int vertex_type = VERTEX_FLAG_NORMALS;

	int stride = 3;
	if (vertex_type & VERTEX_FLAG_NORMALS) {
		stride += 3;
	}
	if (vertex_type & VERTEX_FLAG_TEXCOORDS) {
		stride += 2;
	}

	// Create the VBO for the vertices.
	CU_VEC<float> vertices;
	surface->GenerateVertices(vertex_type, vertices);
	int vertex_count = surface->GetVertexCount();

	// Create a new VBO for the indices if needed.
	int index_count = surface->GetTriangleIndexCount();
	CU_VEC<unsigned short> indices;
	surface->GenerateTriangleIndices(indices);

	mesh->SetRenderBuffer(vertex_type, vertices, indices);
	mesh->SetIndexCount(surface->GetTriangleIndexCount());

	// Init aabb
	for (int i = 0, n = vertices.size(); i < n; )
	{
		sm::vec3 pos;
		pos.x = vertices[i];
		pos.y = vertices[i + 1];
		pos.z = vertices[i + 2];
		aabb.Combine(pos);
		i += stride;
	}

	return mesh;
}

}