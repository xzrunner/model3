#pragma once

namespace n0 { class SceneNode; }
namespace pt3 { class RenderParams; }

namespace n3
{

class RenderSystem
{
public:
	static void Draw(const n0::SceneNode& node, const pt3::RenderParams& params);

}; // RenderSystem

}