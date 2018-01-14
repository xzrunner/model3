#pragma once

#include "node3/INode.h"

#include <SM_Vector.h>

namespace n3
{

class Sprite2Node : public INode
{
public:
	Sprite2Node(const ModelPtr& model);

	virtual bool Update() override { return false; }

private:
	sm::vec2 m_pos;

}; // Sprite2Node

}