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
	sm::mat4 GetProjectionMat() const;
	sm::mat4 GetRotateMat() const;

	float GetNear() const { return m_znear; }
	float GetFar() const { return m_zfar; }
	float GetAspect() const { return m_aspect; }
	float GetAngleOfView() const { return m_angle_of_view; }

	const sm::vec3 GetToward() const { return m_n; }
	
	void SetAspect(float aspect) { m_aspect = aspect; }

	void Reset();

private:
	void InitUVN();

private:
	// model view
	sm::vec3 m_pos, m_target;
	float m_distance;

	sm::vec3 m_up;
	sm::vec3 m_u, m_v, m_n;

	// store for reset
	sm::vec3 m_init_pos;
	sm::vec3 m_init_target;
	sm::vec3 m_init_up;

	// projection
	float m_znear, m_zfar;
	float m_aspect;
	float m_angle_of_view;

}; // Camera

}