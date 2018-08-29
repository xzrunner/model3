#include "node3/RenderSystem.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"
//#include "node3/CompAABB.h"

#include <SM_Matrix.h>
#include <node0/SceneNode.h>
#include <painting3/RenderSystem.h>

namespace n3
{

void RenderSystem::Draw(const n0::SceneNodePtr& node, const pt3::RenderParams& params)
{
	sm::mat4 mt_child, mt_trans;
	if (node->HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node->GetUniqueComp<CompTransform>();
		mt_trans = ctrans.GetTransformMat();
		mt_child = mt_trans * params.mt;
	}

	pt3::RenderParams c_params = params;
	c_params.mt       = mt_child;
	c_params.mt_trans = mt_trans;

	if (node->HasSharedComp<CompModel>())
	{
		auto& cmodel = node->GetUniqueComp<CompModelInst>();
		auto& model = cmodel.GetModel();
		if (model) {
			pt3::RenderSystem::DrawModel(*model, c_params);
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

	//// debug draw aabb
	//if (node->HasUniqueComp<n3::CompAABB>())
	//{
	//	pt3::PrimitiveDraw::SetColor(0xffff0000);
	//	auto& caabb = node->GetUniqueComp<n3::CompAABB>();
	//	pt3::PrimitiveDraw::Cube(mt_trans, caabb.GetAABB());
	//}
}


}