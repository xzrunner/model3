#pragma once

#include <SM_Vector.h>
#include <SM_Quaternion.h>

namespace n3
{

class Ray
{
public:
//	Ray();
	Ray(const sm::vec3& start, const sm::vec3& dir);

	void Translate(const sm::vec3& offset);
//	void Rotate(const sm::mat4& mat);

	void ChangeCoordSystem(const sm::Quaternion& rot);

	const sm::vec3& Start() const;
	sm::vec3 Dir() const;

private:
	sm::vec3 m_start, m_dir_vec;
	sm::Quaternion m_dir;

}; // Ray

}