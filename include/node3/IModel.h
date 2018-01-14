#pragma once

#include "node3/AABB.h"

#include <memory>

#include <cu/uncopyable.h>

namespace n3
{

class RenderParams;

class IModel : private cu::Uncopyable
{
public:
	virtual ~IModel() {}
	virtual size_t Type() const = 0;
	virtual void Draw(const RenderParams&) const = 0;

	void SetAABB(const AABB& aabb) { m_aabb = aabb; }
	const AABB& GetAABB() const { return m_aabb; }

private:
	AABB m_aabb;

}; // IModel

typedef std::shared_ptr<IModel>       ModelPtr;
typedef std::shared_ptr<const IModel> ModelConstPtr;

}