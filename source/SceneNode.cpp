#include "node3/SceneNode.h"

namespace n3
{

void SceneNode::AddChild(const std::shared_ptr<SceneNode>& child)
{
	m_children.push_back(child);
}

void SceneNode::RemoveChild(const std::shared_ptr<SceneNode>& child)
{

}

void SceneNode::SetParent(const std::shared_ptr<SceneNode>& parent)
{
	m_parent = parent;
}

}