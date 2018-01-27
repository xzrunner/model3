#pragma once

#include "node3/SceneNode.h"

#include <SM_Matrix.h>

namespace n3
{

class DrawNode
{
public:
	static void Draw(const SceneNodePtr& node, const sm::mat4& mt);

}; // DrawNode

}