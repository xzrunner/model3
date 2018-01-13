#include "node3/DrawNode.h"
#include "node3/RenderParams.h"

namespace n3
{

void DrawNode::Draw(const NodeConstPtr& node, const RenderParams& rp)
{
	sm::mat4 mt = node->GetMat() * rp.mt;

	auto& angle = node->GetAngle();
	sm::mat4 mt_rot = sm::mat4::Rotated(angle.x, angle.y, angle.z) * rp.mt_rot;

	node->GetModel()->Draw(RenderParams(mt, mt_rot));
}

}