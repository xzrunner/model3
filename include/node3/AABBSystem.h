#pragma once

#include <SM_Cube.h>

namespace n0 { class CompAsset; }

namespace n3
{

class AABBSystem
{
public:
	static sm::cube GetBounding(const n0::CompAsset& casset);

}; // AABBSystem

}