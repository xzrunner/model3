#include "node3/Viewport.h"
#include "node3/Camera.h"

namespace n3
{

Viewport::Viewport()
	: m_width(0)
	, m_height(0)
{
}

void Viewport::SetSize(float width, float height)
{
	m_width  = width;
	m_height = height;
}

sm::vec2 Viewport::TransPos3ProjectToScreen(const sm::vec3& proj, float cam_near, float cam_far) const
{
	float x = cam_near * proj.x / proj.z * m_width * 0.5f ,
		  y = cam_far  * proj.y / proj.z * m_height * 0.5f;
	sm::vec2 pos;
	pos.x = m_width * 0.5f - x;
	pos.y = m_height * 0.5f + y;
	return pos;
}

sm::vec3 Viewport::TransPos3ScreenToProject(const sm::vec2& scr, float proj_z, float cam_near, float cam_far) const
{
	sm::vec3 pos;
	pos.x = -((scr.x / m_width  * 2 - 1) * proj_z) / cam_near;
	pos.y =  ((scr.y / m_height * 2 - 1) * proj_z) / cam_far;
	pos.z = 0;
	return pos;
}

sm::vec3 Viewport::TransPos3ScreenToDir(const sm::vec2& screen, float cam_near) const
{
	sm::vec3 start(0, 0, 0);

	sm::vec3 end;
 	end.z = - cam_near;
	end.x =  (screen.x - m_width  * 0.5f) * 2.0f / m_width;
	end.y = -(screen.y - m_height * 0.5f) * 2.0f / m_width;

	return end - start;
}

sm::vec3 Viewport::MapToSphere(const sm::vec2& touchpoint) const
{
	const float trackball_radius = m_width / 3.0f;
	const sm::vec2 center_point(m_width*0.5f, m_height*0.5f);

	sm::vec2 p = touchpoint - center_point;

	// Flip the Y axis because pixel coords increase towards the bottom.
	p.y = -p.y;

	const float radius = trackball_radius;
	const float safeRadius = radius - 1;

	if (p.Length() > safeRadius) {
		float theta = atan2(p.y, p.x);
		p.x = safeRadius * cos(theta);
		p.y = safeRadius * sin(theta);
	}

	float z = sqrt(radius * radius - p.LengthSquared());
	sm::vec3 mapped = sm::vec3(p.x, p.y, z);
	return mapped / radius;
}

}