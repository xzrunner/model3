#pragma once

#include "node3/Model.h"

#include <node0/NodeComponent.h>

#include <memory>

namespace n3
{

class CompMesh : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::ComponentID TypeID() const override { 
		return n0::GetComponentTypeID<CompMesh>(); }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<Model> m_model = nullptr;

}; // CompMesh

}