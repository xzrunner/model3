#include "node3/Sprite2Model.h"
#include "node3/ModelType.h"

#include <sprite2/DrawNode.h>

namespace n3
{

Sprite2Model::Sprite2Model(const s2::SymPtr& sym)
	: m_symbol(sym)
{
}

size_t Sprite2Model::Type() const
{
	return MODEL_SPRITE2;
}

void Sprite2Model::Draw(const RenderParams&) const
{
	s2::DrawNode::Draw(*m_symbol);
}

}