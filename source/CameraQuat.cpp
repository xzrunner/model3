#include "model3/CameraQuat.h"

namespace m3
{

CameraQuat::CameraQuat()
{
}

void CameraQuat::Translate(const sm::vec3& offset)
{
	m_translation += offset;
}

void CameraQuat::Rotate(const sm::vec3& begin, const sm::vec3& end)
{
	sm::Quaternion rot = sm::Quaternion::CreateFromVectors(begin, end);
	m_orientation.Rotate(rot);
}

sm::mat4 CameraQuat::ToMat() const
{
	sm::mat4 rot(m_orientation);
	sm::mat4 trans;
	trans.Translate(m_translation.x, m_translation.y, m_translation.z);
	return rot * trans;
}

}