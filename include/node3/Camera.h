#pragma once

#include <SM_Vector.h>
#include <SM_Matrix.h>

namespace n3
{

class Camera
{
public:
	Camera();
	Camera(const sm::vec3& pos, const sm::vec3& target, const sm::vec3& up);

	void Slide(float du, float dv, float dn);

	void Roll(float angle);
	void Yaw(float angle);
	void Pitch(float angle);

	void Translate(float dx, float dy);
	void MoveToward(float offset);

	void AimAtTarget();

	const sm::vec3& GetPos() const { return m_pos; }

	sm::mat4 GetModelViewMat() const;

	void Reset(const sm::vec3& pos, const sm::vec3& target, const sm::vec3& up);

private:
	void InitUVN();

private:
	sm::vec3 m_pos, m_target;
	float m_distance;

	sm::vec3 m_up;
	sm::vec3 m_u, m_v, m_n;

}; // Camera

}