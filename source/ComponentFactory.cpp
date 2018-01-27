#include "node3/ComponentFactory.h"

#include "node3/CompAABB.h"
#include "node3/CompMesh.h"
#include "node3/CompModel.h"
#include "node3/CompTransform.h"

namespace n3
{

CU_SINGLETON_DEFINITION(ComponentFactory);

ComponentFactory::ComponentFactory()
{
	m_creator.insert(std::make_pair(CompAABB::TYPE_NAME,
		[](SceneNodePtr& node, const rapidjson::Value& val)
	{
		auto& comp = node->AddComponent<CompAABB>();
		comp.LoadFromJson(val);
	}));

	m_creator.insert(std::make_pair(CompMesh::TYPE_NAME,
		[](SceneNodePtr& node, const rapidjson::Value& val)
	{
		auto& comp = node->AddComponent<CompMesh>();
		comp.LoadFromJson(val);
	}));

	m_creator.insert(std::make_pair(CompModel::TYPE_NAME,
		[](SceneNodePtr& node, const rapidjson::Value& val)
	{
		auto& comp = node->AddComponent<CompModel>();
		comp.LoadFromJson(val);
	}));

	m_creator.insert(std::make_pair(CompTransform::TYPE_NAME,
		[](SceneNodePtr& node, const rapidjson::Value& val)
	{
		auto& comp = node->AddComponent<CompTransform>();
		comp.LoadFromJson(val);
	}));
}

void ComponentFactory::Create(SceneNodePtr& node, 
	                          const std::string& name, 
	                          const rapidjson::Value& val)
{
	auto itr = m_creator.find(name);
	if (itr != m_creator.end()) {
		itr->second(node, val);
	} else {
		GD_REPORT_ASSERT("no comp creator");
	}
}

void ComponentFactory::AddCreator(const std::string& name, const CreateFunc& func)
{
	m_creator.insert(std::make_pair(name, func));
}

}