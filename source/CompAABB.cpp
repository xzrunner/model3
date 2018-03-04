#include "node3/CompAABB.h"

namespace n3
{

const char* const CompAABB::TYPE_NAME = "n3_aabb";

std::unique_ptr<n0::NodeComponent> CompAABB::Clone() const
{
	auto comp = std::make_unique<CompAABB>();
	comp->m_aabb = m_aabb;
	return comp;
}

}