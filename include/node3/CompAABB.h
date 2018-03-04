#pragma once

#include <node0/NodeComponent.h>
#include <painting3/AABB.h>

namespace n3
{

class CompAABB : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	void SetAABB(const pt3::AABB& aabb) { m_aabb = aabb; }
	const pt3::AABB& GetAABB() const { return m_aabb; }

	static const char* const TYPE_NAME;

private:
	pt3::AABB m_aabb;

}; // CompAABB

}