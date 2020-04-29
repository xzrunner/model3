#pragma once

#include <painting0/RenderContext.h>

namespace n0 { class SceneNode; }
namespace pt3 { class RenderParams; }
namespace ur { class Device; class Context; }

namespace n3
{

class RenderSystem
{
public:
	static void Draw(const ur::Device& dev, ur::Context& ur_ctx,
        const n0::SceneNode& node, const pt3::RenderParams& params,
        const pt0::RenderContext& ctx);

}; // RenderSystem

}