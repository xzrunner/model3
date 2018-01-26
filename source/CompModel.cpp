#include "node3/CompModel.h"

namespace n3
{

const char* const CompModel::TYPE_NAME = "model";

bool CompModel::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	if (m_model) {
		return false;
	} else {
		return m_model->StoreToJson(val, alloc);
	}
}

void CompModel::LoadFromJson(const rapidjson::Value& val)
{
	
}

}