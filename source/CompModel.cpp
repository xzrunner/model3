#include "node3/CompModel.h"
#include "node3/ModelFactory.h"
#include "node3/Model.h"

namespace n3
{

const char* const CompModel::TYPE_NAME = "model";

bool CompModel::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	if (m_model) {
		val.SetObject();
		val.AddMember("type", rapidjson::StringRef(m_model->Type()), alloc);
		return m_model->StoreToJson(val, alloc);
	} else {
		return false;
	}
}

void CompModel::LoadFromJson(const rapidjson::Value& val)
{
	std::string type = val["type"].GetString();
	m_model = ModelFactory::Create(type);
	m_model->LoadFromJson(val);
}

}