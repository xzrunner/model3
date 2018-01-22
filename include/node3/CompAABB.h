#pragma once

#include "node3/NodeComponent.h"
#include "node3/AABB.h"

namespace n3
{

class CompAABB : public NodeComponent
{
public:
	CompAABB(SceneNode* entity)
		: NodeComponent(entity)
	{}

	void SetAABB(const AABB& aabb) { m_aabb = aabb; }
	const AABB& GetAABB() const { return m_aabb; }

private:
	AABB m_aabb;

}; // CompAABB

}