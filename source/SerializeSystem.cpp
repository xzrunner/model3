#include "node3/SerializeSystem.h"
#include "node3/ComponentFactory.h"

#include <node0/SceneNode.h>

namespace n3
{

void SerializeSystem::StoreNodeToJson(const n0::SceneNodePtr& node, rapidjson::Value& val,
	                                  rapidjson::MemoryPoolAllocator<>& alloc)
{
	val.SetObject();

	// tree

	rapidjson::Value val_children;
	val_children.SetArray();

	auto& children = node->GetAllChildren();
	int idx = 0;
	for (auto& child : children) 
	{
		rapidjson::Value cval;
		StoreNodeToJson(child, cval, alloc);
		val_children.PushBack(cval, alloc);
	}

	if (!children.empty()) {
		val.AddMember("children", val_children, alloc);
	}

	// components

	rapidjson::Value val_components;
	val_components.SetObject();

	auto& components = node->GetAllComponents();
	for (auto& comp : components)
	{
		rapidjson::Value cval;
		if (comp->StoreToJson(cval, alloc)) {
			val_components.AddMember(rapidjson::StringRef(comp->Type()), cval, alloc);
		}
	}

	if (!components.empty()) {
		val.AddMember("components", val_components, alloc);
	}
}

void SerializeSystem::LoadNodeFromJson(n0::SceneNodePtr& node, const rapidjson::Value& val)
{
	// tree
	if (val.HasMember("children")) 
	{
		for (auto& val_child : val["children"].GetArray()) 
		{
			auto child = std::make_shared<n0::SceneNode>();
			LoadNodeFromJson(child, val_child);
			node->AddChild(child);
			child->SetParent(node);
		}
	}

	// components
	if (val.HasMember("components"))
	{
		auto itr = val["components"].MemberBegin();
		for ( ; itr != val["components"].MemberEnd(); ++itr) {
			ComponentFactory::Instance()->Create(
				node, itr->name.GetString(), itr->value);
		}
	}
}

}