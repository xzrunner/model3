#pragma once

#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace n3
{

class DrawNode
{
public:
	static void Draw(const n0::SceneNodePtr& node, const sm::mat4& mt);

}; // DrawNode

}