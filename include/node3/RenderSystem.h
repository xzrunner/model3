#pragma once

#include <SM_Matrix.h>
#include <node0/SceneNode.h>

namespace n3
{

class Model;

class RenderSystem
{
public:
	static void DrawModel(const Model& model, const sm::mat4& mat);

}; // RenderSystem

}