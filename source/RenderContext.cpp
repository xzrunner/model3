#include "model3/RenderContext.h"

#include <shaderlab/SubjectMVP3.h>

namespace m3
{

void RenderContext::SetModelView(const sm::mat4& mt)
{
	if (m_mv_mat == mt) {
		return;
	}

	m_mv_mat = mt;

	UpdateModelView();
}

void RenderContext::UpdateModelView() const
{
	sl::SubjectMVP3::Instance()->NotifyModelview(m_mv_mat);
}

}