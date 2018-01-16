#pragma once

#include "node3/AABB.h"

#include <cu/uncopyable.h>

#include <string>
#include <memory>

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

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }
	
private:
	AABB m_aabb;

	std::string m_filepath;

}; // IModel

typedef std::shared_ptr<IModel>       ModelPtr;
typedef std::shared_ptr<const IModel> ModelConstPtr;

}