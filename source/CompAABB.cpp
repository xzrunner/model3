#include "node3/CompAABB.h"

namespace n3
{

const char* const CompAABB::TYPE_NAME = "aabb";

bool CompAABB::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	val.SetObject();

	rapidjson::Value val_min;
	auto& min = m_aabb.Min();
	val_min.SetArray();
	val_min.PushBack(min.x, alloc);
	val_min.PushBack(min.y, alloc);
	val_min.PushBack(min.z, alloc);
	val.AddMember("min", val_min, alloc);

	rapidjson::Value val_max;
	auto& max = m_aabb.Max();
	val_max.SetArray();
	val_max.PushBack(min.x, alloc);
	val_max.PushBack(min.y, alloc);
	val_max.PushBack(min.z, alloc);
	val.AddMember("max", val_max, alloc);

	return true;
}

void CompAABB::LoadFromJson(const rapidjson::Value& val)
{
	sm::vec3 min, max;
	min.x = val["min"][0].GetFloat();
	min.y = val["min"][1].GetFloat();
	min.z = val["min"][2].GetFloat();
	max.x = val["max"][0].GetFloat();
	max.y = val["max"][1].GetFloat();
	max.z = val["max"][2].GetFloat();
	m_aabb.Combine(min);
	m_aabb.Combine(max);
}

}