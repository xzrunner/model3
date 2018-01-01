#pragma once

#include <SM_Matrix.h>

namespace m3
{

class RenderContext
{
public:
	RenderContext();

	void SetModelView(const sm::mat4& mt);
	void SetProjection(const sm::mat4& mt);
	void SetScreen(int width, int height);

	void UpdateMVP() const;
	void UpdateModelView() const;
	void UpdateProjection() const;
	void UpdateViewport() const;

private:
	sm::mat4 m_mv_mat;
	sm::mat4 m_proj_mat;

	int m_screen_width;
	int m_screen_height;

}; // RenderContext

}