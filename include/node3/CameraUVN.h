#ifndef _MODEL3_CAMERA_UVN_H_
#define _MODEL3_CAMERA_UVN_H_

#include <SM_Vector.h>
#include <SM_Matrix.h>

namespace m3
{

class CameraUVN
{
public:
	CameraUVN();

	void Translate(const sm::vec3& offset);
	void Zoom(bool zoomin);

	sm::mat4 GetModelViewMat() const;

	const sm::vec3& GetPosition() const { return m_pos; }
	void SetPosition(const sm::vec3& pos) { m_pos = pos; }

	float GetRotHeading() const { return m_rot_heading; }
	void SetRotHeading(float rot_heading) { m_rot_heading = rot_heading; }
	float GetRotElevation() const { return m_rot_elevation; }
	void SetRotElevation(float rot_elevation) { m_rot_elevation = rot_elevation; }

	void Rotate(float dheading, float delevation);

	sm::vec3 GetLeft() const;		// U
	sm::vec3 GetUp() const;			// V
	sm::vec3 GetToward() const;		// N

	void SetScreenSize(int width, int height);

	sm::vec3 MapToSphere(sm::ivec2 touchpoint) const;

	void Reset();

public:
	static const float CAM_NEAR;
	static const float CAM_FAR;

private:
	sm::mat4 GetModelViewRotMat() const;

private:
	sm::vec3 m_pos;
	
	// use UVN model
	// in degree
	float m_rot_heading;	// ��λ��
	float m_rot_elevation;	// ����

	int m_width, m_height;

}; // CameraUVN
	
}

#endif // _MODEL3_CAMERA_UVN_H_