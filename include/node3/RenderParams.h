#pragma once

#include <SM_Matrix.h>

namespace n3
{

class RenderParams
{
public:
	sm::mat4 mt;
	sm::mat4 mt_rot;

public:
	RenderParams(const sm::mat4& mt, const sm::mat4& mt_rot) 
		: mt(mt), mt_rot(mt_rot) {}

}; // RenderParams

}