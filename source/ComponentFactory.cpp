#include "node3/ComponentFactory.h"

#include "node3/CompAABB.h"
#include "node3/CompMesh.h"
#include "node3/CompModel.h"
#include "node3/CompTransform.h"

namespace n3
{

void ComponentFactory::Create(SceneNodePtr& node, 
	                          const std::string& name, 
	                          const rapidjson::Value& val)
{
	if (name == CompAABB::TYPE_NAME) {
		auto& comp = node->AddComponent<n3::CompAABB>();
		comp.LoadFromJson(val);
	} else if (name == CompMesh::TYPE_NAME) {
		auto& comp = node->AddComponent<n3::CompMesh>();
		comp.LoadFromJson(val);
	} else if (name == CompModel::TYPE_NAME) {
		auto& comp = node->AddComponent<n3::CompModel>();
		comp.LoadFromJson(val);
	} else if (name == CompTransform::TYPE_NAME) {
		auto& comp = node->AddComponent<n3::CompTransform>();
		comp.LoadFromJson(val);
	}
}

}