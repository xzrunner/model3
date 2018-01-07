#include "node3/Camera.h"

#include "sm_const.h"

namespace n3
{

Camera::Camera()
{
}

Camera::Camera(const sm::vec3& pos, const sm::vec3& target, const sm::vec3& up)
	: m_pos(pos)
	, m_target(target)
	, m_up(up)
{
	m_distance = (pos - target).Length();
	InitUVN();
}

void Camera::Slide(float du, float dv, float dn)
{
	m_pos.x    = m_pos.x + du * m_u.x + dv * m_v.x + dn * m_n.x;
	m_pos.y    = m_pos.y + du * m_u.y + dv * m_v.y + dn * m_n.y;
	m_pos.z    = m_pos.z + du * m_u.z + dv * m_v.z + dn * m_n.z;
	m_target.x = m_target.x + du * m_u.x + dv * m_v.x + dn * m_n.x;
	m_target.y = m_target.x + du * m_u.y + dv * m_v.y + dn * m_n.y;
	m_target.z = m_target.x + du * m_u.z + dv * m_v.z + dn * m_n.z;
}

void Camera::Roll(float angle)
{
	float cs = cos(angle * SM_DEG_TO_RAD);
	float sn = sin(angle * SM_DEG_TO_RAD);
	sm::vec3 t(m_u);
	sm::vec3 s(m_v);

	m_u.x = cs * t.x - sn * s.x;
	m_u.y = cs * t.y - sn * s.y;
	m_u.z = cs * t.z - sn * s.z;

	m_v.x = sn * t.x + cs * s.x;
	m_v.y = sn * t.y + cs * s.y;
	m_v.z = sn * t.z + cs * s.z;
}

void Camera::Yaw(float angle)
{
	float cs = cos(angle * SM_DEG_TO_RAD);
	float sn = sin(angle * SM_DEG_TO_RAD);
	sm::vec3 t(m_n);
	sm::vec3 s(m_u);

	m_n.x = cs * t.x - sn * s.x;
	m_n.y = cs * t.y - sn * s.y;
	m_n.z = cs * t.z - sn * s.z;

	m_u.x = sn * t.x + cs * s.x;
	m_u.y = sn * t.y + cs * s.y;
	m_u.z = sn * t.z + cs * s.z;
}

void Camera::Pitch(float angle)
{
	float cs = cos(angle * SM_DEG_TO_RAD);
	float sn = sin(angle * SM_DEG_TO_RAD);
	sm::vec3 t(m_v);
	sm::vec3 s(m_n);

	m_v.x = cs * t.x - sn * s.x;
	m_v.y = cs * t.y - sn * s.y;
	m_v.z = cs * t.z - sn * s.z;

	m_n.x = sn * t.x + cs * s.x;
	m_n.y = sn * t.y + cs * s.y;
	m_n.z = sn * t.z + cs * s.z;
}

void Camera::Translate(float dx, float dy)
{
	sm::vec3 tx = - m_u * dx,
		     ty = m_v * dy;
	m_pos += tx;
	m_pos += ty;
	m_target += tx;
	m_target += ty;
}

void Camera::MoveToward(float offset)
{
	m_pos += m_n * offset;
	m_distance = (m_pos - m_target).Length();
}

void Camera::AimAtTarget()
{
	m_pos = m_target + m_n * m_distance;
}

sm::mat4 Camera::GetModelViewMat() const
{
	sm::mat4 mat;
	float* m = mat.x;
	m[0] = m_u.x; m[4] = m_u.y; m[8] = m_u.z; m[12] = - m_pos.Dot(m_u);
	m[1] = m_v.x; m[5] = m_v.y; m[9] = m_v.z; m[13] = - m_pos.Dot(m_v);
	m[2] = m_n.x; m[6] = m_n.y; m[10]= m_n.z; m[14] = - m_pos.Dot(m_n);
	m[3] = 0;     m[7] = 0;     m[11]= 0;     m[15] = 1.0;
	return mat;
}

void Camera::Reset(const sm::vec3& pos, const sm::vec3& target, const sm::vec3& up)
{
	m_pos    = pos;
	m_target = target;
	m_up     = up;

	m_distance = (pos - target).Length();

	InitUVN();
}

void Camera::InitUVN()
{
	m_n = (m_pos - m_target).Normalized();
	m_u = m_up.Cross(m_n).Normalized();
	m_v = m_n.Cross(m_u).Normalized();
}

}