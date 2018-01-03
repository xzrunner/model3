#include "node3/DrawNode.h"
#include "node3/RenderParams.h"

namespace n3
{

void DrawNode::Draw(const NodeConstPtr& node, const RenderParams& rp)
{
	RenderParams rp_child;
	rp_child.mt = node->GetMat() * rp.mt;
	node->GetModel()->Draw(rp);
}

}