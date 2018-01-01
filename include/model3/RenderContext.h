#pragma once

#include <SM_Matrix.h>

namespace m3
{

class RenderContext
{
public:

	void SetModelView(const sm::mat4& mt);
	
	void UpdateModelView() const;

private:
	sm::mat4 m_mv_mat;

}; // RenderContext

}