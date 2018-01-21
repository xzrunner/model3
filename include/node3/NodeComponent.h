#pragma once

namespace n3
{

using ComponentID = size_t;

namespace Internal
{
inline ComponentID GetUniqueComponentID() noexcept
{
    static ComponentID id{0u};
    return id++;
}
}

template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
    static_assert(std::is_base_of<NodeComponent, T>::value,
        "T must inherit from Component");

    static ComponentID type_id{Internal::GetUniqueComponentID()};
    return type_id;
}

class SceneNode;
class NodeComponent
{
public:
	NodeComponent(SceneNode* entity) 
		: m_entity(entity) {}
	virtual ~NodeComponent() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

private:
	SceneNode* m_entity = nullptr;

}; // NodeComponent

}