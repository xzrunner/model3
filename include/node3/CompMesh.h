#pragma once

#include "node3/NodeComponent.h"
#include "node3/Model.h"

#include <memory>

namespace n3
{

class CompMesh : NodeComponent
{
public:

private:
	std::unique_ptr<Model> m_model = nullptr;

}; // CompMesh

}