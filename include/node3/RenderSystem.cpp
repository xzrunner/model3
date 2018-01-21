#include "node3/RenderSystem.h"
#include "node3/Material.h"
#include "node3/ResourceAPI.h"
#include "node3/Model.h"
#include "node3/Mesh.h"
#include "node3/n3_typedef.h"

#include <shaderlab/ShaderMgr.h>
#include <shaderlab/Model3Shader.h>

namespace n3
{

void RenderSystem::DrawModel(const Model& model, const sm::mat4& mat)
{
	sl::ShaderMgr* mgr = sl::ShaderMgr::Instance();
	mgr->SetShader(sl::MODEL3);
	sl::Model3Shader* shader = static_cast<sl::Model3Shader*>(mgr->GetShader());

	shader->SetLightPosition(sm::vec3(0.25f, 0.25f, 1));
	shader->SetModelview(mat);
	shader->SetNormalMatrix(mat);

	auto& meshes = model.GetAllMeshes();
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