#pragma once

#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace model { class Model; }

namespace n3
{

class RenderSystem
{
public:
	static void DrawModel(const model::Model& model, const sm::mat4& mat);

}; // RenderSystem

}