#include "node3/CompTransform.h"

namespace n3
{

const char* const CompTransform::TYPE_NAME = "n3_transform";

CompTransform::CompTransform()
	: m_scale(1, 1, 1)
{
}

sm::mat4 CompTransform::GetTransformMat() const
{
	auto mt_scale = sm::mat4::Scaled(m_scale.x, m_scale.y, m_scale.z);
	auto mt_rot = sm::mat4(m_angle);
	auto mt_trans = sm::mat4::Translated(m_position.x, m_position.y, m_position.z);
	return mt_scale * mt_rot * mt_trans;
}

}