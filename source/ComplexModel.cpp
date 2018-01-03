#include "node3/ComplexModel.h"
#include "node3/ModelType.h"
#include "node3/DrawNode.h"

namespace n3
{

size_t ComplexModel::Type() const
{
	return MODEL_COMPLEX;
}

void ComplexModel::Draw(const RenderParams& rp) const
{
	for (auto& child : m_children) {
		DrawNode::Draw(child, rp);
	}
}

void ComplexModel::AddChild(const NodePtr& node)
{
	m_children.push_back(node);
}

}