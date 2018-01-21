#pragma once

#include "node3/NodeComponent.h"

#include <memory>
#include <vector>
#include <bitset>
#include <array>

namespace n3
{

class SceneNode
{
public:

	template <typename T>
	bool HasComponent() const;

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args);

	template <typename T>
	T& GetComponent() const;

private:
	// tree
	std::weak_ptr<SceneNode> m_parent;
	std::vector<std::shared_ptr<SceneNode>> m_children;

	// components
	std::vector<std::unique_ptr<NodeComponent>> m_components;

	static const size_t MAX_COMPONENTS = 32;
	std::bitset<MAX_COMPONENTS>         m_component_bitset;
	std::array<uint8_t, MAX_COMPONENTS> m_component_array;

}; // SceneNode

using SceneNodePtr = std::shared_ptr<SceneNode>;

}

#include "node3/SceneNode.inl"