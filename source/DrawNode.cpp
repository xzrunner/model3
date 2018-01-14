#include "node3/DrawNode.h"
#include "node3/RenderParams.h"

namespace n3
{

void DrawNode::Draw(const NodeConstPtr& node, const RenderParams& rp)
{
	auto& pos = node->GetPos();
	auto mt_trans = sm::mat4::Translated(pos.x, pos.y, pos.z);
	auto mt_rot = sm::mat4(node->GetAngle());
	
	RenderParams child_rp(mt_rot * mt_trans * rp.mt);
	node->GetModel()->Draw(child_rp);
}

}