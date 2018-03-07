#pragma once

#include <node0/NodeUniqueComp.h>
#include <painting3/AABB.h>

namespace n3
{

class CompAABB : public n0::NodeUniqueComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompAABB>(); 
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void SetAABB(const pt3::AABB& aabb) { m_aabb = aabb; }
	const pt3::AABB& GetAABB() const { return m_aabb; }

	static const char* const TYPE_NAME;

private:
	pt3::AABB m_aabb;

}; // CompAABB

}