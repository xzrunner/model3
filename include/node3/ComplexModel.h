#pragma once

#include "node3/IModel.h"
#include "node3/INode.h"

#include <vector>

namespace n3
{

class ComplexModel : public IModel
{
public:

	virtual size_t Type() const override;
	virtual void Draw(const RenderParams&) const override;

	void AddChild(const NodePtr& node);
	const std::vector<NodePtr>& GetAllChildren() const { return m_children; }

private:
	std::vector<NodePtr> m_children;

}; // ComplexModel

}