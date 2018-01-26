#include "node3/CompTransform.h"

namespace n3
{

const char* const CompTransform::TYPE_NAME = "transform";

CompTransform::CompTransform()
	: m_scale(1, 1, 1)
{
}

bool CompTransform::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	val.SetObject();

	if (m_position != sm::vec3(0, 0, 0))
	{
		rapidjson::Value val_pos;
		val_pos.SetArray();
		val_pos.PushBack(m_position.x, alloc);
		val_pos.PushBack(m_position.y, alloc);
		val_pos.PushBack(m_position.z, alloc);
		val.AddMember("position", val_pos, alloc);
	}

	if (m_angle != sm::Quaternion())
	{
		rapidjson::Value val_angle;
		val_angle.SetArray();
		float roll, pitch, yaw;
		sm::Quaternion::TransToEulerAngle(m_angle, roll, pitch, yaw);
		val_angle.PushBack(pitch, alloc);
		val_angle.PushBack(yaw, alloc);
		val_angle.PushBack(roll, alloc);
		val.AddMember("angle", val_angle, alloc);
	}

	if (m_scale != sm::vec3(1, 1, 1))
	{
		rapidjson::Value val_scale;
		val_scale.SetArray();
		val_scale.PushBack(m_scale.x, alloc);
		val_scale.PushBack(m_scale.y, alloc);
		val_scale.PushBack(m_scale.z, alloc);
		val.AddMember("scale", val_scale, alloc);
	}

	return true;
}

void CompTransform::LoadFromJson(const rapidjson::Value& val)
{
	if (val.HasMember("position"))
	{
		m_position.x = val["position"][0].GetFloat();
		m_position.y = val["position"][1].GetFloat();
		m_position.z = val["position"][2].GetFloat();
	}

	if (val.HasMember("angle"))
	{
		float pitch = val["angle"][0].GetFloat();
		float yaw   = val["angle"][1].GetFloat();
		float roll  = val["angle"][2].GetFloat();
		m_angle = sm::Quaternion::CreateFromEulerAngle(roll, pitch, yaw);
	}

	if (val.HasMember("scale"))
	{
		m_scale.x = val["scale"][0].GetFloat();
		m_scale.y = val["scale"][1].GetFloat();
		m_scale.z = val["scale"][2].GetFloat();
	}
}

sm::mat4 CompTransform::GetTransformMat() const
{
	auto mt_scale = sm::mat4::Scaled(m_scale.x, m_scale.y, m_scale.z);
	auto mt_rot = sm::mat4(m_angle);
	auto mt_trans = sm::mat4::Translated(m_position.x, m_position.y, m_position.z);
	return mt_scale * mt_rot * mt_trans;
}

}