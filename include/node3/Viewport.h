#pragma once

#include <SM_Vector.h>

namespace n3
{

class Viewport
{
public:
	Viewport();

	void SetSize(float width, float height);

	sm::vec2 TransPos3ProjectToScreen(const sm::vec3& proj, float cam_near, float cam_far) const;
	sm::vec3 TransPos3ScreenToProject(const sm::vec2& scr, float proj_z, float cam_near, float cam_far) const;

	sm::vec3 TransPos3ScreenToDir(const sm::vec2& screen, float cam_near) const;

	sm::vec3 MapToSphere(const sm::vec2& touchpoint) const;

private:
	float m_width, m_height;

}; // Viewport

}