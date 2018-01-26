#pragma once

#include "node3/SceneNode.h"

namespace n3
{

class ComponentFactory
{
public:
	static void Create(SceneNodePtr& node, const std::string& name, 
		const rapidjson::Value& val);

}; // ComponentFactory

}