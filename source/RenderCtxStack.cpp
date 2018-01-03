#include "node3/RenderCtxStack.h"

namespace n3
{

CU_SINGLETON_DEFINITION(RenderCtxStack)

RenderCtxStack::RenderCtxStack() 
{
}

RenderCtxStack::~RenderCtxStack() 
{
}

int RenderCtxStack::Push(const RenderContext& ctx)
{
	int idx = m_stack.size();
	BindCtx(ctx);
	m_stack.push_back(ctx);
	return idx;
}

void RenderCtxStack::Pop()
{
	if (m_stack.empty()) {
		return;
	}

	m_stack.pop_back();

	if (!m_stack.empty()) {
		BindCtx(m_stack.back());		
	}
}

const RenderContext* RenderCtxStack::Top() const
{
	if (m_stack.empty()) {
		return nullptr;
	} else {
		return &m_stack[m_stack.size() - 1];
	}
}

bool RenderCtxStack::Bind(int idx)
{
	if (idx < 0 || idx > static_cast<int>(m_stack.size())) {
		return false;
	}
	BindCtx(m_stack[idx]);
	return true;
}

void RenderCtxStack::BindCtx(const RenderContext& ctx)
{
	//ctx.UpdateMVP();
	//ctx.UpdateViewport();

	ctx.UpdateModelView();
}

}