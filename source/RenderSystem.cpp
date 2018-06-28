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
	// flush shader status
	sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr().BindRenderShader(nullptr, sl::EXTERN_SHADER);

	auto& nodes = model.model->sk_anim.GetAllAnims();
	if (nodes.empty()) {
		DrawMesh(*model.model, mat);
	} else {
		DrawSkeletalNode(model, 0, mat);
//		DrawSkeletalNodeDebug(model, 0, mat);
	}
}

void RenderSystem::DrawMesh(const model::Model& model, const sm::mat4& mat)
{
	auto mgr = pt3::EffectsManager::Instance();
	for (auto& mesh : model.meshes)
	{
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
		for (auto& sub : geo.sub_geometries)
		{
			if (sub.index) {
				ur::Blackboard::Instance()->GetRenderContext().DrawElementsVAO(
					ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
			} else {
				ur::Blackboard::Instance()->GetRenderContext().DrawArraysVAO(
					ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
			}
		}
	}
}

void RenderSystem::DrawSkeletalNode(const model::ModelInstance& model_inst, int node_idx, const sm::mat4& mat)
{
	auto& model = *model_inst.model;
	auto& nodes = model.sk_anim.GetAllNodes();
	auto& node = *nodes[node_idx];
	if (!node.children.empty())
	{
		assert(node.meshes.empty());
		for (auto& child : node.children) {
			DrawSkeletalNode(model_inst, child, mat);
		}
	}
	else
	{
		auto mgr = pt3::EffectsManager::Instance();
		auto child_mat = model_inst.global_trans[node_idx] * mat;
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

			auto& bone_trans = model_inst.CalcBoneMatrices(node_idx, mesh_idx);
			if (!bone_trans.empty()) {
				mgr->SetBoneMatrixes(effect, &bone_trans[0], bone_trans.size());
			} else {
				sm::mat4 mat;
				mgr->SetBoneMatrixes(effect, &mat, 1);
			}

			mgr->SetLightPosition(effect, sm::vec3(0.25f, 0.25f, 1));
			mgr->SetProjMat(effect, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
			mgr->SetNormalMat(effect, child_mat);

			mgr->SetMaterial(effect, material->ambient, material->diffuse,
				material->specular, material->shininess);

			mgr->SetModelViewMat(effect, child_mat.x);

			auto& geo = mesh->geometry;
			for (auto& sub : geo.sub_geometries)
			{
				if (sub.index) {
					ur::Blackboard::Instance()->GetRenderContext().DrawElementsVAO(
						ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
				} else {
					ur::Blackboard::Instance()->GetRenderContext().DrawArraysVAO(
						ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
				}
			}
		}
	}
}

void RenderSystem::DrawSkeletalNodeDebug(const model::ModelInstance& model_inst, int node_idx, const sm::mat4& mat)
{
	auto& model = *model_inst.model;

	auto& nodes = model.sk_anim.GetAllNodes();
	auto& node = *nodes[node_idx];
	for (auto& child : node.children)
	{
		auto& ptrans = model_inst.global_trans[node_idx];
		auto& ctrans = model_inst.global_trans[child];
		pt3::PrimitiveDraw::Line(mat * ptrans.GetTranslate(), mat * ctrans.GetTranslate());

		assert(node.meshes.empty());
		for (auto& child : node.children) {
			DrawSkeletalNodeDebug(model_inst, child, mat);
		}
	}
}

}