#include "node3/ObjectModel.h"
#include "node3/ModelType.h"
#include "node3/ResourceAPI.h"
#include "node3/Material.h"
#include "node3/Mesh.h"
#include "node3/n3_typedef.h"
#include "node3/RenderParams.h"

#include <shaderlab/ShaderMgr.h>
#include <shaderlab/Model3Shader.h>

namespace n3
{

size_t ObjectModel::Type() const
{
	return MODEL_OBJECT;
}

void ObjectModel::Draw(const RenderParams& rp) const
{
	sl::ShaderMgr* mgr = sl::ShaderMgr::Instance();
	mgr->SetShader(sl::MODEL3);
	sl::Model3Shader* shader = static_cast<sl::Model3Shader*>(mgr->GetShader());

	shader->SetLightPosition(sm::vec3(0.25f, 0.25f, 1));

	auto& meshes = m_model->GetAllMeshes();
	for (auto& mesh : meshes)
	{
		const n3::Material& material = mesh->GetMaterial();
		int tex_id = n3::ResourceAPI::GetTexID(material.texture);
		shader->SetMaterial(sl::Model3Shader::Material(material.ambient, 
			material.diffuse, material.specular, material.shininess, tex_id));

		int vertex_type = mesh->GetVertexType();
		bool has_normal = vertex_type & n3::VERTEX_FLAG_NORMALS;
		bool has_texcoord = vertex_type & n3::VERTEX_FLAG_TEXCOORDS;

		// transform vertices
		auto vertices = mesh->GetVertices();
		int stride = 3;
		if (has_normal) {
			stride += 3;
		}
		if (has_texcoord) {
			stride += 2;
		}
		assert(vertices.size() % stride == 0);
		for (int i = 0, n = vertices.size(); i < n; i += stride) {
			sm::vec3 pos = rp.mt * sm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
			memcpy(&vertices[i], &pos.xyz[0], sizeof(float) * 3);
			if (has_normal) {
				sm::vec3 normal = rp.mt * sm::vec3(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
				memcpy(&vertices[i + 3], &normal.xyz[0], sizeof(float) * 3);
			}
		}

		auto& indieces = mesh->GetIndices();
		shader->Draw(&vertices[0], vertices.size(), &indieces[0], indieces.size(), has_normal, has_texcoord);
	}
}

}