#pragma once

#include <node0/NodeComponent.h>

#include <memory>

namespace n3
{

class Model;

class CompModel : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::ComponentID TypeID() const override { 
		return n0::GetComponentTypeID<CompModel>(); }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	void SetModel(const std::shared_ptr<Model>& model) { m_model = model; }
	const std::shared_ptr<Model>& GetModel() const { return m_model; }
		
	static const char* const TYPE_NAME;

private:
	std::shared_ptr<Model> m_model = nullptr;

}; // CompModel

}