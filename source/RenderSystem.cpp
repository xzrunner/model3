#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"
#include "node3/CompAABB.h"

#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>
#include <unirender/Shader.h>
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
#include <quake/Lightmaps.h>

namespace
{

#define MAX_BATCH_SIZE 4096

static unsigned int vbo_indices[MAX_BATCH_SIZE];
static unsigned int num_vbo_indices;

void FlushBatch(ur::DRAW_MODE mode)
{
	if (num_vbo_indices > 0)
	{
		auto& rc = ur::Blackboard::Instance()->GetRenderContext();
		rc.DrawElements(mode, num_vbo_indices, vbo_indices);

		num_vbo_indices = 0;
	}
}

}

namespace n3
{

void RenderSystem::Draw(const n0::SceneNodePtr& node, const RenderParams& params)
{
	sm::mat4 mt_child, mt_trans;
	if (node->HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node->GetUniqueComp<CompTransform>();
		mt_trans = ctrans.GetTransformMat();
		mt_child = mt_trans * params.mt;
	}

	RenderParams c_params = params;
	c_params.mt = mt_child;

	if (node->HasSharedComp<CompModel>())
	{
		auto& cmodel = node->GetUniqueComp<CompModelInst>();
		auto& model = cmodel.GetModel();
		if (model) {
			RenderSystem::DrawModel(*model, c_params);
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

	//// debug draw
	//if (node->HasUniqueComp<n3::CompAABB>())
	//{
	//	pt3::PrimitiveDraw::SetColor(0xffff0000);
	//	auto& caabb = node->GetUniqueComp<n3::CompAABB>();
	//	pt3::PrimitiveDraw::Cube(mt_trans, caabb.GetAABB());
	//}
}

void RenderSystem::DrawModel(const model::ModelInstance& model_inst, const RenderParams& params)
{
	auto& model = model_inst.GetModel();
	auto& ext = model->ext;
	if (ext)
	{
		switch (ext->Type())
		{
		case model::EXT_MORPH_TARGET:
			DrawMorphAnim(*model, params);
			break;
		case model::EXT_SKELETAL:
			DrawSkeletalNode(model_inst, 0, params);
			//DrawSkeletalNodeDebug(model, 0, params.mt);
			break;
		case model::EXT_BSP:
			DrawBSP(*model, params);
			break;
		}
	}
	else
	{
		DrawMesh(*model, params);
	}
}

void RenderSystem::DrawMesh(const model::Model& model, const RenderParams& params)
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();

	auto mgr = pt3::EffectsManager::Instance();
	auto& meshes = params.type == RenderParams::DRAW_MESH ? model.meshes : model.border_meshes;
	for (auto& mesh : meshes)
	{
		ur::TexturePtr tex = nullptr;

		auto& material = model.materials[mesh->material];
		if (material->diffuse_tex != -1) {
			tex = model.textures[material->diffuse_tex].second;
			if (tex) {
				ur::Blackboard::Instance()->GetRenderContext().BindTexture(tex->TexID(), 0);
			}
		}

		auto effect_type = pt3::EffectsManager::EffectType(mesh->effect);
		auto effect = mgr->Use(effect_type);
		effect->DrawBefore(tex);

		mgr->SetProjMat(effect_type, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
		mgr->SetModelViewMat(effect_type, params.mt.x);

		mgr->SetMaterial(effect_type, material->ambient, material->diffuse,
			material->specular, material->shininess);

		if (mesh->effect == pt3::EffectsManager::EFFECT_DEFAULT ||
			mesh->effect == pt3::EffectsManager::EFFECT_DEFAULT_NO_TEX) {
			mgr->SetLightPosition(effect_type, sm::vec3(0.25f, 0.25f, 1));
			mgr->SetNormalMat(effect_type, params.mt);
		}

		auto& geo = mesh->geometry;
		auto mode = effect->GetDrawMode();
		for (auto& sub : geo.sub_geometries)
		{
			if (geo.vao > 0)
			{
				if (sub.index) {
					ur::Blackboard::Instance()->GetRenderContext().DrawElementsVAO(
						mode, sub.offset, sub.count, geo.vao);
				} else {
					ur::Blackboard::Instance()->GetRenderContext().DrawArraysVAO(
						mode, sub.offset, sub.count, geo.vao);
				}
			}
			else
			{
				auto& sub = geo.sub_geometries[0];
				if (geo.ebo) {
					rc.BindBuffer(ur::INDEXBUFFER, geo.ebo);
					rc.BindBuffer(ur::VERTEXBUFFER, geo.vbo);
					rc.DrawElements(mode, sub.offset, sub.count);
				} else {
					rc.BindBuffer(ur::VERTEXBUFFER, geo.vbo);
					rc.DrawArrays(mode, sub.offset, sub.count);
				}
			}
		}
	}
}

void RenderSystem::DrawMorphAnim(const model::Model& model, const RenderParams& params)
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

		auto effect_type = pt3::EffectsManager::EffectType(mesh->effect);
		auto effect = mgr->Use(effect_type);

		mgr->SetLightPosition(effect_type, sm::vec3(0.25f, 0.25f, 1));
		mgr->SetProjMat(effect_type, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
		mgr->SetNormalMat(effect_type, params.mt);

		mgr->SetMaterial(effect_type, material->ambient, material->diffuse,
			material->specular, material->shininess);

		mgr->SetModelViewMat(effect_type, params.mt.x);

		auto& geo = mesh->geometry;
//		assert(frame >= 0 && frame < geo.sub_geometries.size());
		//if (geo.vao > 0)
		//{
		//	auto& sub = geo.sub_geometries[frame];
		//	if (sub.index) {
		//		rc.DrawElementsVAO(
		//			mode, sub.offset, sub.count, geo.vao);
		//	} else {
		//		rc.DrawArraysVAO(
		//			mode, sub.offset, sub.count, geo.vao);
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
			rc.DrawArrays(effect->GetDrawMode(), sub.offset, sub.count);
		}
	}
}

void RenderSystem::DrawSkeletalNode(const model::ModelInstance& model_inst, int node_idx, const RenderParams& params)
{
	auto& model = *model_inst.GetModel();
	auto& g_trans = model_inst.GetGlobalTrans();
	auto& nodes = static_cast<model::SkeletalAnim*>(model.ext.get())->GetAllNodes();
	auto& node = *nodes[node_idx];
	if (!node.children.empty())
	{
		assert(node.meshes.empty());
		for (auto& child : node.children) {
			DrawSkeletalNode(model_inst, child, params);
		}
	}
	else
	{
		auto mgr = pt3::EffectsManager::Instance();
		auto child_mat = g_trans[node_idx] * params.mt;
		assert(node.children.empty());
		for (auto& mesh_idx : node.meshes)
		{
			auto& mesh = model.meshes[mesh_idx];

			auto& material = model.materials[mesh->material];
			if (material->diffuse_tex != -1) {
				int tex_id = model.textures[material->diffuse_tex].second->TexID();
				ur::Blackboard::Instance()->GetRenderContext().BindTexture(tex_id, 0);
			}

			auto effect_type = pt3::EffectsManager::EffectType(mesh->effect);
			auto effect = mgr->Use(effect_type);
			auto mode = effect->GetDrawMode();

			auto& bone_trans = model_inst.CalcBoneMatrices(node_idx, mesh_idx);
			if (!bone_trans.empty()) {
				mgr->SetBoneMatrixes(effect_type, &bone_trans[0], bone_trans.size());
			} else {
				sm::mat4 mat;
				mgr->SetBoneMatrixes(effect_type, &mat, 1);
			}

			mgr->SetLightPosition(effect_type, sm::vec3(0.25f, 0.25f, 1));
			mgr->SetProjMat(effect_type, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
			mgr->SetNormalMat(effect_type, child_mat);

			mgr->SetMaterial(effect_type, material->ambient, material->diffuse,
				material->specular, material->shininess);

			mgr->SetModelViewMat(effect_type, child_mat.x);

			auto& geo = mesh->geometry;
			for (auto& sub : geo.sub_geometries)
			{
				if (sub.index) {
					ur::Blackboard::Instance()->GetRenderContext().DrawElementsVAO(
						mode, sub.offset, sub.count, geo.vao);
				} else {
					ur::Blackboard::Instance()->GetRenderContext().DrawArraysVAO(
						mode, sub.offset, sub.count, geo.vao);
				}
			}
		}
	}
}

void RenderSystem::DrawSkeletalNodeDebug(const model::ModelInstance& model_inst, int node_idx, const RenderParams& params)
{
	auto& model = *model_inst.GetModel();
	auto& g_trans = model_inst.GetGlobalTrans();

	auto& nodes = static_cast<model::SkeletalAnim*>(model.ext.get())->GetAllNodes();
	auto& node = *nodes[node_idx];
	for (auto& child : node.children)
	{
		auto& ptrans = g_trans[node_idx];
		auto& ctrans = g_trans[child];
		pt3::PrimitiveDraw::Line(params.mt * ptrans.GetTranslate(), params.mt * ctrans.GetTranslate());

		assert(node.meshes.empty());
		for (auto& child : node.children) {
			DrawSkeletalNodeDebug(model_inst, child, params);
		}
	}
}

void RenderSystem::DrawBSP(const model::Model& model, const RenderParams& params)
{
	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	rc.SetCull(ur::CULL_DISABLE);

	auto mgr = pt3::EffectsManager::Instance();
	auto effect_type = pt3::EffectsManager::EFFECT_BSP;
	auto effect = mgr->Use(effect_type);
	auto mode = effect->GetDrawMode();
	mgr->SetProjMat(effect_type, pt3::Blackboard::Instance()->GetWindowContext()->GetProjMat().x);
	mgr->SetModelViewMat(effect_type, params.mt.x);

	num_vbo_indices = 0;

	rc.BindBuffer(ur::VERTEXBUFFER, model.meshes[0]->geometry.vbo);

	int last_lightmap = -1;

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
			if (s->lightmaptexturenum != last_lightmap)
			{
				FlushBatch(mode);
				last_lightmap = s->lightmaptexturenum;
				int texid = quake::Lightmaps::Instance()->GetTexID(s->lightmaptexturenum);
				rc.BindTexture(texid, 1);
			}

			int num_surf_indices = 3 * (s->numedges - 2);
			if (num_vbo_indices + num_surf_indices > MAX_BATCH_SIZE) {
				FlushBatch(mode);
			}

			for (int i = 2; i < s->numedges; ++i)
			{
				vbo_indices[num_vbo_indices++] = s->vbo_firstvert;
				vbo_indices[num_vbo_indices++] = s->vbo_firstvert + i - 1;
				vbo_indices[num_vbo_indices++] = s->vbo_firstvert + i;
			}

			s = s->next;
		}

		FlushBatch(mode);
	}
}

}