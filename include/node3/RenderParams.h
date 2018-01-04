#pragma once

#include <SM_Matrix.h>

namespace n3
{

class RenderParams
{
public:
	sm::mat4 mt;

public:
	RenderParams(const sm::mat4& mt) : mt(mt) {}

}; // RenderParams

}