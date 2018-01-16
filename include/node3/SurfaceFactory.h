#pragma once

#include <string>

namespace n3
{

class Surface;

class SurfaceFactory
{
public:
	static Surface* Create(const std::string& name);

}; // SurfaceFactory

}