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
#include <model/SkeletalAnim.h>
#include <model/MorphTargetAnim.h>
#include <model/BspModel.h>
#include <node0/SceneNode.h>
#include <painting3/Blackboard.h>
#include <painting3/WindowContext.h>
#include <painting3/EffectsManager.h>
#include <painting3/PrimitiveDraw.h>

namespace
{

#define MAX_BATCH_SIZE 4096

static unsigned int vbo_indices[MAX_BATCH_SIZE];
static unsigned int num_vbo_indices;

void FlushBatch()
{
	if (num_vbo_indices > 0)
	{
		auto& rc = ur::Blackboard::Instance()->GetRenderContext();
		rc.DrawElements(ur::DRAW_TRIANGLES, num_vbo_indices, vbo_indices);

		num_vbo_indices = 0;
	}
}

}

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

	auto& ext = model.model->ext;
	if (ext)
	{
		switch (ext->Type())
		{
		case model::EXT_MORPH_TARGET:
			DrawMorphAnim(*model.model, mat);
			break;
		case model::EXT_SKELETAL:
			DrawSkeletalNode(model, 0, mat);
			//DrawSkeletalNodeDebug(model, 0, mat);
			break;
		case model::EXT_BSP:
			DrawBSP(*model.model, mat);
			break;
		}
	}
	else
	{
		DrawMesh(*model.model, mat);
	}
}

void RenderSystem::DrawMesh(const model::Model& model, const sm::mat4& mat)
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();

	auto mgr = pt3::EffectsManager::Instance();
	for (auto& mesh : model.meshes)
	{
		auto& material = model.materials[mesh->material];
		if (material->diffuse_tex != -1) {
			int tex_id = model.textures[material->diffuse_tex].second->TexID();
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
			if (geo.vao > 0)
			{
				if (sub.index) {
					ur::Blackboard::Instance()->GetRenderContext().DrawElementsVAO(
						ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
				} else {
					ur::Blackboard::Instance()->GetRenderContext().DrawArraysVAO(
						ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
				}
			}
			else
			{
				auto& sub = geo.sub_geometries[0];
				if (geo.ebo) {
					rc.BindBuffer(ur::INDEXBUFFER, geo.ebo);
					rc.BindBuffer(ur::VERTEXBUFFER, geo.vbo);
					rc.DrawElements(ur::DRAW_TRIANGLES, sub.offset, sub.count);
				} else {
					rc.BindBuffer(ur::VERTEXBUFFER, geo.vbo);
					rc.DrawArrays(ur::DRAW_TRIANGLES, sub.offset, sub.count);
				}
			}
		}
	}
}

void RenderSystem::DrawMorphAnim(const model::Model& model, const sm::mat4& mat)
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();

	auto anim = static_cast<model::MorphTargetAnim*>(model.ext.get());
	int frame = anim->GetFrame();
	assert(frame < anim->GetNumFrames());
	int stride = anim->GetNumVertices() * (4 * 3 * 2);

	auto mgr = pt3::EffectsManager::Instance();
	for (auto& mesh : model.meshes)
	{
		auto& material = model.materials[mesh->material];
		if (material->diffuse_tex != -1) {
			int tex_id = model.textures[material->diffuse_tex].second->TexID();
			rc.BindTexture(tex_id, 0);
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
//		assert(frame >= 0 && frame < geo.sub_geometries.size());
		//if (geo.vao > 0)
		//{
		//	auto& sub = geo.sub_geometries[frame];
		//	if (sub.index) {
		//		rc.DrawElementsVAO(
		//			ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
		//	} else {
		//		rc.DrawArraysVAO(
		//			ur::DRAW_TRIANGLES, sub.offset, sub.count, geo.vao);
		//	}
		//}
		//else
		{
			// update anim blend
			mgr->SetMorphAnimBlend(anim->GetBlend());

			// pose1_vert, pose1_normal
			int offset = stride * frame;
			geo.vertex_layout[0].offset = offset;
			geo.vertex_layout[1].offset = offset;
			// pose2_vert, pose2_normal
			offset += stride;
			geo.vertex_layout[2].offset = offset;
			geo.vertex_layout[3].offset = offset;
			// update vertex layout
			rc.UpdateVertexLayout(geo.vertex_layout);

			auto& sub = geo.sub_geometries[0];
			rc.BindBuffer(ur::VERTEXBUFFER, geo.vbo);
			rc.DrawArrays(ur::DRAW_TRIANGLES, sub.offset, sub.count);
		}
	}
}

void RenderSystem::DrawSkeletalNode(const model::ModelInstance& model_inst, int node_idx, const sm::mat4& mat)
{
	auto& model = *model_inst.model;
	auto& nodes = static_cast<model::SkeletalAnim*>(model.ext.get())->GetAllNodes();
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
				int tex_id = model.textures[material->diffuse_tex].second->TexID();
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

	auto& nodes = static_cast<model::SkeletalAnim*>(model.ext.get())->GetAllNodes();
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

void RenderSystem::DrawBSP(const model::Model& model, const sm::mat4& mat)
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	rc.SetCull(ur::CULL_DISABLE);

	auto mgr = pt3::EffectsManager::Instance();
	auto effect = pt3::EffectsManager::EFFECT_BSP;
	mgr->Use(effect);
	mgr->SetProjMat(effect, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
	mgr->SetModelViewMat(effect, mat.x);

	num_vbo_indices = 0;

	rc.BindBuffer(ur::VERTEXBUFFER, model.meshes[0]->geometry.vbo);

	auto bsp = static_cast<model::BspModel*>(model.ext.get());
	for (auto& tex : bsp->textures)
	{
		if (!tex.surfaces_chain || !tex.tex) {
			continue;
		}

		rc.BindTexture(tex.tex->TexID(), 0);

		auto s = tex.surfaces_chain;
		while (s)
		{
			int num_surf_indices = 3 * (s->numedges - 2);
			if (num_vbo_indices + num_surf_indices > MAX_BATCH_SIZE) {
				FlushBatch();
			}

			for (int i = 2; i < s->numedges; ++i)
			{
				vbo_indices[num_vbo_indices++] = s->vbo_firstvert;
				vbo_indices[num_vbo_indices++] = s->vbo_firstvert + i - 1;
				vbo_indices[num_vbo_indices++] = s->vbo_firstvert + i;
			}

			s = s->next;
		}

		FlushBatch();
	}
}

}