#include "node3/RenderContext.h"

#include <shaderlab/SubjectMVP3.h>
#include <shaderlab/Blackboard.h>
#include <shaderlab/RenderContext.h>
#include <unirender/RenderContext.h>

namespace n3
{

RenderContext::RenderContext()
	: m_screen_width(0)
	, m_screen_height(0)
{
}

void RenderContext::SetModelView(const sm::mat4& mt)
{
	if (m_mv_mat == mt) {
		return;
	}

	m_mv_mat = mt;

	UpdateModelView();
}

void RenderContext::SetProjection(const sm::mat4& mt)
{
	if (m_proj_mat == mt) {
		return;
	}

	m_proj_mat = mt;

	UpdateProjection();
}

void RenderContext::SetScreen(int width, int height)
{
	m_screen_width = width;
	m_screen_height = height;

	UpdateViewport();
}

void RenderContext::UpdateMVP() const
{
	UpdateModelView();
	UpdateProjection();
}

void RenderContext::UpdateModelView() const
{
	sl::Blackboard::Instance()->GetRenderContext().GetSubMVP3().NotifyModelview(m_mv_mat);
}

void RenderContext::UpdateProjection() const
{
	sl::Blackboard::Instance()->GetRenderContext().GetSubMVP3().NotifyProjection(m_proj_mat);
}

void RenderContext::UpdateViewport() const
{
	if (m_screen_width == 0 && m_screen_height == 0) {
		return;
	}

	auto& ur_rc = sl::Blackboard::Instance()->GetRenderContext().GetContext();
	ur_rc.SetViewport(0, 0, m_screen_width, m_screen_height);
}

}