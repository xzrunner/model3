#pragma once

#include "node3/NodeComponent.h"
#include "node3/Model.h"

#include <memory>

namespace n3
{

class CompMesh : public NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<Model> m_model = nullptr;

}; // CompMesh

}