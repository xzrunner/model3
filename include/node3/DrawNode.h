#pragma once

#include "node3/INode.h"

namespace n3
{

class RenderParams;

class DrawNode
{
public:
	static void Draw(const NodeConstPtr& node, const RenderParams& rp);

}; // DrawNode

}