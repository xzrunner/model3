#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"
#include "node3/RenderSystem.h"

#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>
#include <shaderlab/Blackboard.h>
#include <shaderlab/RenderContext.h>
#include <model/Model.h>
#include <model/ModelInstance.h>
#include <model/Callback.h>
#include <node0/SceneNode.h>
#include <painting3/Blackboard.h>
#include <painting3/WindowContext.h>
#include <painting3/EffectsManager.h>
#include <painting3/PrimitiveDraw.h>

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
		auto& cmodel = node->GetUniqueComp<CompModelInst>();
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

void RenderSystem::DrawModel(const model::ModelInstance& model, const sm::mat4& mat)
{
	if (model.model->nodes.empty()) {
		return;
	}

	// flush shader status
	sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr().BindRenderShader(nullptr, sl::EXTERN_SHADER);

	if (!model.model->nodes.empty()) {
//		DrawModelNode(model, 0, mat);
		DrawModelNodeDebug(model, 0, mat);
	}
}

void RenderSystem::DrawModelNode(const model::ModelInstance& model_inst, int node_idx, const sm::mat4& mat)
{
	auto& model = *model_inst.model;

	auto& node = *model.nodes[node_idx];
	if (!node.children.empty())
	{
		assert(node.meshes.empty());
		auto child_mat = node.local_trans * mat;
		for (auto& child : node.children) {
			DrawModelNode(model_inst, child, child_mat);
		}
	}
	else
	{
		auto mgr = pt3::EffectsManager::Instance();

		assert(node.children.empty());
		for (auto& mesh_idx : node.meshes)
		{
			auto& mesh = model.meshes[mesh_idx];

			auto& material = model.materials[mesh->material];
			if (material->diffuse_tex != -1) {
				int tex_id = model::Callback::GetTexID(model.textures[material->diffuse_tex].second);
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

void RenderSystem::DrawModelNodeDebug(const model::ModelInstance& model_inst, int node_idx, const sm::mat4& mat)
{
	auto& model = *model_inst.model;

	auto& node = *model.nodes[node_idx];
	for (auto& child : node.children)
	{
		auto& ptrans = model_inst.global_trans[node_idx];
		auto& ctrans = model_inst.global_trans[child];
		pt3::PrimitiveDraw::Line(mat * ptrans.GetTranslate(), mat * ctrans.GetTranslate());

		assert(node.meshes.empty());
		for (auto& child : node.children) {
			DrawModelNodeDebug(model_inst, child, mat);
		}
	}
}

}