#pragma once

#include "node3/INode.h"

namespace n3
{

class ComplexNode : public INode
{
public:

	virtual bool Update() override { return false; }

private:

}; // ComplexNode

}