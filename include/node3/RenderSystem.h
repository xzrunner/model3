#pragma once

#include <node0/typedef.h>

namespace pt3 { class RenderParams; }

namespace n3
{

class RenderSystem
{
public:
	static void Draw(const n0::SceneNodePtr& node,
		const pt3::RenderParams& params);

}; // RenderSystem

}