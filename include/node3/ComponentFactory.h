#pragma once

#include "node3/SceneNode.h"

#include <cu/cu_macro.h>

#include <functional>
#include <map>

namespace n3
{

class ComponentFactory
{
public:
	using CreateFunc = std::function<void(SceneNodePtr&, const rapidjson::Value&)>;

	void Create(SceneNodePtr& node, const std::string& name, 
		const rapidjson::Value& val);

	void AddCreator(const std::string& name, const CreateFunc& func);

private:
	std::map<std::string, CreateFunc> m_creator;

	CU_SINGLETON_DECLARATION(ComponentFactory);

}; // ComponentFactory

}