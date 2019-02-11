#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"
#include "node3/CompImage3D.h"
#include "node3/CompMeshFilter.h"

#include <SM_Matrix.h>
#include <node0/SceneNode.h>
#include <node0/CompMaterial.h>
#include <painting3/RenderSystem.h>

namespace n3
{

void RenderSystem::Draw(const n0::SceneNode& node,
                        const pt3::RenderParams& params,
                        const pt3::RenderContext& ctx)
{
	sm::mat4 mt_child, mt_trans;
	if (node.HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node.GetUniqueComp<CompTransform>();
		mt_trans = ctrans.GetTransformMat();
		mt_child = mt_trans * params.mt;
	}

	pt3::RenderParams c_params = params;
	c_params.mt       = mt_child;
	c_params.mt_trans = mt_trans;

	// asset
	if (node.HasSharedComp<n0::CompAsset>())
	{
		auto& casset = node.GetSharedComp<n0::CompAsset>();
		auto asset_type = casset.AssetTypeID();
		if (asset_type == n0::GetAssetUniqueTypeID<CompModel>())
		{
			auto& cmodel_inst = node.GetUniqueComp<CompModelInst>();
			auto& model_inst = cmodel_inst.GetModel();
			if (model_inst)
            {
                auto& cmodel = node.GetSharedComp<CompModel>();
                auto& mats = cmodel.GetAllMaterials();
				pt3::RenderSystem::DrawModel(*model_inst, mats, c_params, ctx);
			}
		}
		else if (asset_type == n0::GetAssetUniqueTypeID<CompImage3D>())
		{
			auto& cimg = static_cast<const CompImage3D&>(casset);
			auto& tex = cimg.GetTexture();
			if (tex) {
				pt3::RenderSystem::DrawTex3D(*tex, c_params);
			}
		}
	}

    // mesh
    if (node.HasUniqueComp<n3::CompMeshFilter>())
    {
        auto& cmesh = node.GetUniqueComp<n3::CompMeshFilter>();
        auto& mesh = cmesh.GetMesh();
        if (node.HasUniqueComp<n0::CompMaterial>())
        {
            auto& cmat = node.GetUniqueComp<n0::CompMaterial>();
            auto& mat = cmat.GetMaterial();
            if (mesh && mat) {
                pt3::RenderSystem::DrawMesh(mesh->geometry, *mat, c_params, ctx);
            }
        }
    }

	//if (node.HasSharedComp<n0::CompComplex>())
	//{
	//	auto& ccomplex = node.GetSharedComp<n0::CompComplex>();
	//	auto& children = ccomplex.GetAllChildren();
	//	for (auto& child : children) {
	//		Draw(child, mt_child);
	//	}
	//}

	//// debug draw aabb
	//if (node.HasUniqueComp<n3::CompAABB>())
	//{
	//	pt3::PrimitiveDraw::SetColor(0xffff0000);
	//	auto& caabb = node.GetUniqueComp<n3::CompAABB>();
	//	pt3::PrimitiveDraw::Cube(mt_trans, caabb.GetAABB());
	//}
}


}