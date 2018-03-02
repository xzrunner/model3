#include "node3/DrawNode.h"
#include "node3/CompTransform.h"
#include "node3/CompModel.h"
#include "node3/RenderSystem.h"

#include <node0/SceneNode.h>
#include <node0/CompComplex.h>

namespace n3
{

void DrawNode::Draw(const n0::SceneNodePtr& node, const sm::mat4& mt)
{
	auto& ctrans = node->GetComponent<CompTransform>();
	sm::mat4 mt_child = ctrans.GetTransformMat() * mt;

	if (node->HasComponent<CompModel>())
	{
		auto& cmodel = node->GetComponent<CompModel>();
		auto& model = cmodel.GetModel();
		if (model) {
			RenderSystem::DrawModel(*model, mt_child);
		}
	}

	if (node->HasComponent<n0::CompComplex>())
	{
		auto& ccomplex = node->GetComponent<n0::CompComplex>();
		auto& children = ccomplex.GetAllChildren();
		for (auto& child : children) {
			Draw(child, mt_child);
		}
	}
}

}