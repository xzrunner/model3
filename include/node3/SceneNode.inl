#pragma once

#include "node3/NodeComponent.h"
#include "node3/CompTransform.h"

namespace n3
{

template <typename T>
bool SceneNode::HasComponent() const 
{
	return m_component_bitset[GetComponentTypeID<T>()];
}

template <typename T, typename... TArgs>
T& SceneNode::AddComponent(TArgs&&... args)
{
	assert(!HasComponent<T>());

	auto comp_ptr = std::make_unique<T>(this, std::forward<TArgs>(args)...);
	auto& comp = *comp_ptr;
	size_t idx = m_components.size();
	assert(idx < 256);
	m_components.emplace_back(std::move(comp_ptr));

	m_component_array[GetComponentTypeID<T>()]  = static_cast<uint8_t>(idx);
	m_component_bitset[GetComponentTypeID<T>()] = true;

	comp.Init();
	return comp;
}

template <typename T>
T& SceneNode::GetComponent() const
{
	assert(HasComponent<T>());
	auto ptr(m_components[m_component_array[GetComponentTypeID<T>()]].get());
	return *reinterpret_cast<T*>(ptr);
}

}