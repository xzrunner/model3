#pragma once

#include <rapidjson/document.h>
#include <node0/SceneNode.h>

namespace n3
{

class SerializeSystem
{
public:
	static void StoreNodeToJson(const n0::SceneNodePtr& node, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc);
	static void LoadNodeFromJson(n0::SceneNodePtr& node, const rapidjson::Value& val);

}; // SerializeSystem

}