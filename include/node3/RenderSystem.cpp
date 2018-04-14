#include "node3/RenderSystem.h"
#include "node3/ResourceAPI.h"

#include <shaderlab/Blackboard.h>
#include <shaderlab/ShaderMgr.h>
#include <shaderlab/RenderContext.h>
#include <shaderlab/Model3Shader.h>
#include <model/Material.h>
#include <model/Model.h>
#include <model/Mesh.h>
#include <model/typedef.h>

namespace n3
{

void RenderSystem::DrawModel(const model::Model& model, const sm::mat4& mat)
{
	auto& shader_mgr = sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr();
	shader_mgr.SetShader(sl::MODEL3);
	sl::Model3Shader* shader = static_cast<sl::Model3Shader*>(shader_mgr.GetShader());

	shader->SetLightPosition(sm::vec3(0.25f, 0.25f, 1));
	shader->SetModelview(mat);
	shader->SetNormalMatrix(mat);

	auto& meshes = model.GetAllMeshes();
	for (auto& mesh : meshes)
	{
		auto& material = mesh->GetMaterial();
		int tex_id = ResourceAPI::GetTexID(material.texture);
		shader->SetMaterial(sl::Model3Shader::Material(material.ambient, 
			material.diffuse, material.specular, material.shininess, tex_id));

		int vertex_type = mesh->GetVertexType();
		bool has_normal = vertex_type & model::VERTEX_FLAG_NORMALS;
		bool has_texcoord = vertex_type & model::VERTEX_FLAG_TEXCOORDS;

		auto& vertices = mesh->GetVertices();
		auto& indieces = mesh->GetIndices();
		shader->Draw(&vertices[0], vertices.size(), &indieces[0], indieces.size(), has_normal, has_texcoord);
	}	
}

}