#include "node3/CompTransform.h"

namespace n3
{

const char* const CompTransform::TYPE_NAME = "n3_transform";

CompTransform::CompTransform()
	: m_scale(1, 1, 1)
{
}

std::unique_ptr<n0::NodeUniqueComp> CompTransform::Clone() const
{
	auto comp = std::make_unique<CompTransform>();
	comp->m_position = m_position;
	comp->m_angle    = m_angle;
	comp->m_scale    = m_scale;
	return comp;
}

sm::mat4 CompTransform::GetTransformMat() const
{
	auto mt_scale = sm::mat4::Scaled(m_scale.x, m_scale.y, m_scale.z);
	auto mt_rot = sm::mat4(m_angle);
	auto mt_trans = sm::mat4::Translated(m_position.x, m_position.y, m_position.z);
	return mt_scale * mt_rot * mt_trans;
}

}