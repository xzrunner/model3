#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"
#include "node3/CompImage3D.h"
#include "node3/CompMeshFilter.h"
#include "node3/CompCloth.h"
#include "node3/CompRigid.h"
#include "node3/CompShape.h"

#include <SM_Matrix.h>
#include <uniphysics/rigid/Body.h>
#include <tessellation/Painter.h>
#include <node0/SceneNode.h>
#include <node0/CompMaterial.h>
#include <painting3/RenderSystem.h>
#include <painting3/MaterialMgr.h>

namespace n3
{

void RenderSystem::Draw(const n0::SceneNode& node,
                        const pt3::RenderParams& params,
                        const pt0::RenderContext& ctx)
{
	sm::mat4 child_world_model, child_local_model;
	if (node.HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node.GetUniqueComp<CompTransform>();
		child_local_model = ctrans.GetTransformMat();
		child_world_model = params.model_world * child_local_model;
	}
    else
    {
        child_world_model = params.model_world;
    }

	pt3::RenderParams c_params = params;
	c_params.model_world = child_world_model;
	c_params.model_local = child_local_model;

    pt0::RenderContext c_ctx = ctx;
    c_ctx.AddVar(
        pt3::MaterialMgr::PosTransUniforms::model.name,
        pt0::RenderVariant(c_params.model_world)
    );
    auto normal_mat = c_params.model_world.Inverted().Transposed();
    c_ctx.AddVar(
        pt3::MaterialMgr::PositionUniforms::normal_mat.name,
        pt0::RenderVariant(sm::mat3(normal_mat))
    );

	// asset
	if (node.HasSharedComp<n0::CompAsset>())
	{
		auto& casset = node.GetSharedComp<n0::CompAsset>();
		auto asset_type = casset.AssetTypeID();
		if (asset_type == n0::GetAssetUniqueTypeID<CompModel>() &&
            !params.mask[pt3::RenderParams::NotDrawModel])
		{
			auto& cmodel_inst = node.GetUniqueComp<CompModelInst>();
			auto& model_inst = cmodel_inst.GetModel();
			if (model_inst)
            {
                auto& cmodel = node.GetSharedComp<CompModel>();
                auto& mats = cmodel.GetAllMaterials();
				pt3::RenderSystem::DrawModel(*model_inst, mats, c_params, c_ctx);
			}
		}
		else if (asset_type == n0::GetAssetUniqueTypeID<CompImage3D>() &&
                 !params.mask[pt3::RenderParams::NotDrawImage])
		{
			auto& cimg = static_cast<const CompImage3D&>(casset);
			auto& tex = cimg.GetTexture();
			if (tex) {
				pt3::RenderSystem::DrawTex3D(*tex, c_params);
			}
		}
	}

    // shape
    if (node.HasUniqueComp<CompShape>() &&
        !params.mask[pt3::RenderParams::NotDrawShape])
    {
        auto& cshape = node.GetUniqueComp<CompShape>();
        auto& shapes = cshape.GetShapes();
        for (auto& s : shapes) {
            assert(s);
            pt3::RenderSystem::DrawShape(*s, params);
        }
    }

    // mesh
    if (node.HasUniqueComp<CompMeshFilter>())
    {
        auto& cmesh = node.GetUniqueComp<CompMeshFilter>();
        auto& mesh = cmesh.GetMesh();
        if (node.HasUniqueComp<n0::CompMaterial>())
        {
            auto& cmat = node.GetUniqueComp<n0::CompMaterial>();
            auto& mat = cmat.GetMaterial();
            if (mesh && mat) {
                pt3::RenderSystem::DrawMesh(mesh->geometry, *mat, c_ctx);
            }
        }
    }

    // physics
    if (node.HasUniqueComp<CompCloth>() &&
        !params.mask[pt3::RenderParams::NotDrawCloth])
    {
        auto& ccloth = node.GetUniqueComp<CompCloth>();
        auto& render_mesh = ccloth.GetRenderMesh();
        if (render_mesh) {
            pt3::RenderSystem::DrawMesh(render_mesh->geometry, pt0::Material(), c_ctx);
        }
    }
    //if (node.HasUniqueComp<CompRigid>())
    //{
    //    auto& crigid = node.GetUniqueComp<CompRigid>();
    //    auto pos = crigid.GetBody()->GetPosition();

    //    sm::vec3 line[2];
    //    line[0] = line[1] = pos;
    //    line[0].x -= 10;
    //    line[1].x += 10;
    //    pt3::RenderSystem::DrawLines3D(2, line[0].xyz, 0xff0000ff);
    //}

	//if (node.HasSharedComp<n0::CompComplex>())
	//{
	//	auto& ccomplex = node.GetSharedComp<n0::CompComplex>();
	//	auto& children = ccomplex.GetAllChildren();
	//	for (auto& child : children) {
	//		Draw(child, mt_child);
	//	}
	//}

	//// debug draw aabb
	//if (node.HasUniqueComp<CompAABB>())
	//{
	//	pt3::PrimitiveDraw::SetColor(0xffff0000);
	//	auto& caabb = node.GetUniqueComp<CompAABB>();
	//	pt3::PrimitiveDraw::Cube(mt_trans, caabb.GetAABB());
	//}
}


}