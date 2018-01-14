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
	shader->SetModelview(rp.mt);
	shader->SetNormalMatrix(rp.mt);

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

		auto& vertices = mesh->GetVertices();
		auto& indieces = mesh->GetIndices();
		shader->Draw(&vertices[0], vertices.size(), &indieces[0], indieces.size(), has_normal, has_texcoord);
	}
}

}