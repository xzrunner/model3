#pragma once

#include "node3/IModel.h"

#include <sprite2/Symbol.h>

namespace n3
{

class Sprite2Model : public IModel
{
public:
	Sprite2Model(const s2::SymPtr& sym);

	virtual size_t Type() const override;
	virtual void Draw(const RenderParams&) const override;
	
private:
	s2::SymPtr m_symbol = nullptr;

}; // Sprite2Model

}