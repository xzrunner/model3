#pragma once

#include "node3/IModel.h"
#include "node3/Model.h"

namespace n3
{

class ObjectModel : public IModel
{
public:
	virtual size_t Type() const override;
	virtual void Draw(const RenderParams&) const override;

	void SetModel(const std::shared_ptr<Model>& model) { m_model = model; }
	const std::shared_ptr<Model>& GetModel() const { return m_model; }

private:
	std::shared_ptr<Model> m_model = nullptr;

}; // ObjectModel

}