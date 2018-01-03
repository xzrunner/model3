#pragma once

#include "node3/INode.h"

namespace n3
{

class ObjectNode : public INode
{
public:

	virtual bool Update() override { return false; }

private:
	

}; // ObjectNode

}