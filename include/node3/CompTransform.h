#pragma once

#include "node3/NodeComponent.h"

#include <SM_Vector.h>
#include <SM_Quaternion.h>
#include <SM_Matrix.h>

namespace n3
{

class CompTransform : public NodeComponent
{
public:
	CompTransform(SceneNode* entity)
		: NodeComponent(entity)
		, m_scale(1, 1, 1) 
	{}

	void SetPosition(const sm::vec3& pos) {
		m_position = pos;
	}

	sm::mat4 GetTransformMat() const 
	{
		auto mt_scale = sm::mat4::Scaled(m_scale.x, m_scale.y, m_scale.z);
		auto mt_rot = sm::mat4(m_angle);
		auto mt_trans = sm::mat4::Translated(m_position.x, m_position.y, m_position.z);
		return mt_trans * mt_rot * mt_scale;
	}

private:
	sm::vec3       m_position;
	sm::Quaternion m_angle;
	sm::vec3       m_scale;

}; // CompTransform

}