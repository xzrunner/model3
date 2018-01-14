#pragma once

#include "node3/INode.h"

namespace n3
{

class ObjectNode : public INode
{
public:
	ObjectNode(const ModelPtr& model);

	virtual bool Update() override { return false; }

private:
	

}; // ObjectNode

}