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

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<Model> m_model = nullptr;

}; // CompMesh

}