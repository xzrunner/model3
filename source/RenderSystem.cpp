#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/RenderSystem.h"

#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>
#include <shaderlab/Blackboard.h>
#include <shaderlab/RenderContext.h>
#include <model/Scene.h>
#include <model/Callback.h>
#include <node0/SceneNode.h>
#include <painting3/Blackboard.h>
#include <painting3/WindowContext.h>
#include <painting3/EffectsManager.h>

namespace n3
{

void RenderSystem::Draw(const n0::SceneNodePtr& node, const sm::mat4& mt)
{
	sm::mat4 mt_child;
	if (node->HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node->GetUniqueComp<CompTransform>();
		mt_child = ctrans.GetTransformMat() * mt;
	}

	if (node->HasSharedComp<CompModel>())
	{
		auto& cmodel = node->GetSharedComp<CompModel>();
		auto& scene = cmodel.GetScene();
		if (scene) {
			RenderSystem::DrawModel(*scene, mt_child);
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

void RenderSystem::DrawModel(const model::Scene& scene, const sm::mat4& mat)
{
	if (scene.nodes.empty()) {
		return;
	}

	// flush shader status
	sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr().BindRenderShader(nullptr, sl::EXTERN_SHADER);

	DrawNode(scene, *scene.nodes.front(), mat);
}

void RenderSystem::DrawNode(const model::Scene& scene, const model::Scene::Node& node, const sm::mat4& mat)
{
	if (!node.children.empty())
	{
		assert(node.meshes.empty());
		auto child_mat = node.local_mat * mat;
		for (auto& child : node.children) {
			DrawNode(scene, *scene.nodes[child], child_mat);
		}
	}
	else
	{
		auto mgr = pt3::EffectsManager::Instance();

		assert(node.children.empty());
		for (auto& mesh_idx : node.meshes)
		{
			auto& mesh = scene.meshes[mesh_idx];

			auto& material = scene.materials[mesh->material];
			if (material->diffuse_tex != -1) {
				int tex_id = model::Callback::GetTexID(scene.textures[material->diffuse_tex].second);
				ur::Blackboard::Instance()->GetRenderContext().BindTexture(tex_id, 0);
			}

			auto effect = pt3::EffectsManager::EffectType(mesh->effect);

			mgr->Use(effect);

			mgr->SetLightPosition(effect, sm::vec3(0.25f, 0.25f, 1));
			mgr->SetProjMat(effect, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
			mgr->SetNormalMat(effect, mat);

			mgr->SetMaterial(effect, material->ambient, material->diffuse,
				material->specular, material->shininess);
			mgr->SetModelViewMat(effect, mat.x);

			auto& geo = mesh->geometry;
			for (auto& sub : geo.sub_geometries) {
				ur::Blackboard::Instance()->GetRenderContext().DrawElementsVAO(
					ur::DRAW_TRIANGLES, sub.index_offset, sub.index_count, geo.vao);
			}
		}
	}
}

}