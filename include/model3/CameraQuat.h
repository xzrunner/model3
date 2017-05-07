#ifndef _MODEL3_CAMERA_QUAT_H_
#define _MODEL3_CAMERA_QUAT_H_

#include <SM_Vector.h>
#include <SM_Quaternion.h>
#include <SM_Matrix.h>

namespace m3
{

class CameraQuat
{
public:
	CameraQuat();

	void Translate(const sm::vec3& offset);
	void Rotate(const sm::vec3& begin, const sm::vec3& end);

	sm::mat4 ToMat() const;

private:
	sm::vec3 m_translation;

	sm::Quaternion m_orientation;

}; // CameraQuat

}

#endif // _MODEL3_CAMERA_QUAT_H_