#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/RenderSystem.h"

#include <shaderlab/Blackboard.h>
#include <shaderlab/ShaderMgr.h>
#include <shaderlab/RenderContext.h>
#include <shaderlab/Model3Shader.h>
#include <model/Model.h>
#include <model/Mesh.h>
#include <model/typedef.h>
#include <model/Callback.h>
#include <node0/SceneNode.h>

namespace n3
{

void RenderSystem::Draw(const n0::SceneNodePtr& node, const sm::mat4& mt)
{
	auto& ctrans = node->GetUniqueComp<CompTransform>();
	sm::mat4 mt_child = ctrans.GetTransformMat() * mt;

	if (node->HasSharedComp<CompModel>())
	{
		auto& cmodel = node->GetSharedComp<CompModel>();
		auto& model = cmodel.GetModel();
		if (model) {
			RenderSystem::DrawModel(*model, mt_child);
		}
	}

	//if (node->HasSharedComp<n0::CompComplex>())
	//{
	//	auto& ccomplex = node->GetSharedComp<n0::CompComplex>();
	//	auto& children = ccomplex.GetAllChildren();
	//	for (auto& child : children) {
	//		Draw(child, mt_child);
	//	}
	//}
}

//void RenderSystem::DrawModel(const model::Model& model, const sm::mat4& mat)
//{
//	auto& shader_mgr = sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr();
//	shader_mgr.SetShader(sl::MODEL3);
//	sl::Model3Shader* shader = static_cast<sl::Model3Shader*>(shader_mgr.GetShader());
//
//	shader->SetLightPosition(sm::vec3(0.25f, 0.25f, 1));
//	shader->SetModelview(mat);
//	shader->SetNormalMatrix(mat);
//
//	auto& meshes = model.GetAllMeshes();
//	for (auto& mesh : meshes)
//	{
//		auto& material = mesh->GetMaterial();
//		int tex_id = -1;
//		if (material.texture) {
//			tex_id = ResourceAPI::GetTexID(material.texture);
//		}
//		shader->SetMaterial(sl::Model3Shader::Material(material.ambient,
//			material.diffuse, material.specular, material.shininess, tex_id));
//
//		int vertex_type = mesh->GetVertexType();
//		bool has_normal = vertex_type & model::VERTEX_FLAG_NORMALS;
//		bool has_texcoord = vertex_type & model::VERTEX_FLAG_TEXCOORDS;
//
//		auto& vertices = mesh->GetVertices();
//		auto& indieces = mesh->GetIndices();
//		shader->Draw(&vertices[0], vertices.size(), &indieces[0], indieces.size(), has_normal, has_texcoord);
//	}
//}

void RenderSystem::DrawModel(const model::Model& model, const sm::mat4& mat)
{
	auto& shader_mgr = sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr();
	shader_mgr.SetShader(sl::MODEL3);
	sl::Model3Shader* shader = static_cast<sl::Model3Shader*>(shader_mgr.GetShader());

	shader->SetLightPosition(sm::vec3(0.25f, 0.25f, 1));
	shader->SetModelview(mat);
	shader->SetNormalMatrix(mat);

	auto& meshes = model.GetAllMeshes();
	int last_mat = -1;
	for (auto& mesh : meshes)
	{
		GD_ASSERT(mesh->geometry.sub_geometries.size() == mesh->geometry.sub_geometry_materials.size(), "err material");
		for (int i = 0, n = mesh->geometry.sub_geometries.size(); i < n; ++i)
		{
			int curr_mat = mesh->geometry.sub_geometry_materials[i];
			// bind material
			if (curr_mat != last_mat)
			{
				if (mesh->materials.empty())
				{
					auto& material = mesh->old_materials[curr_mat];
					int tex_id = -1;
					if (material.texture) {
						tex_id = model::Callback::GetTexID(material.texture);
					}
					shader->SetMaterial(sl::Model3Shader::Material(material.ambient,
						material.diffuse, material.specular, material.shininess, tex_id));
				}
				else
				{
					auto& material = mesh->materials[curr_mat];
					int tex_id = -1;
					if (material.texture) {
						tex_id = model::Callback::GetTexID(material.texture);
					}
					model::MaterialOld old_mat;
					shader->SetMaterial(sl::Model3Shader::Material(old_mat.ambient,
						old_mat.diffuse, old_mat.specular, old_mat.shininess, tex_id));
				}
				last_mat = curr_mat;
			}

			auto& sub = mesh->geometry.sub_geometries[i];
			shader->DrawVAO(
				mesh->geometry.vao,
				sub.index_count,
				sub.index_offset,
				mesh->geometry.vertex_type & model::VERTEX_FLAG_NORMALS,
				mesh->geometry.vertex_type & model::VERTEX_FLAG_TEXCOORDS
			);
		}
	}
}

}