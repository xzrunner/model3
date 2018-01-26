#pragma once

#include "node3/SceneNode.h"

#include <rapidjson/document.h>

namespace n3
{

class SerializeSystem
{
public:
	static void StoreNodeToJson(const SceneNodePtr& node, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc);
	static void LoadNodeFromJson(SceneNodePtr& node, const rapidjson::Value& val);

}; // SerializeSystem

}