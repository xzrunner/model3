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
	auto& meshes = m_model->GetAllMeshes();
	for (auto& mesh : meshes)
	{
		const n3::Material& material = mesh->GetMaterial();
		int tex_id = n3::ResourceAPI::GetTexID(material.texture);
		shader->SetMaterial(material.ambient, material.diffuse, material.specular,
			material.shininess, tex_id);
		shader->SetLightPosition(sm::vec3(0.25f, 0.25f, 1));
		shader->SetNormalMatrix(rp.mt);

		int vertex_type = mesh->GetVertexType();
		bool normal = vertex_type & n3::VERTEX_FLAG_NORMALS;
		bool texcoords = vertex_type & n3::VERTEX_FLAG_TEXCOORDS;
		shader->Draw(mesh->GetVertices(), mesh->GetIndices(), normal, texcoords);
	}
}

}