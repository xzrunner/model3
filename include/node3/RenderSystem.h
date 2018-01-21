#pragma once

#include "node3/SceneNode.h"

#include <SM_Matrix.h>

namespace n3
{

class Model;

class RenderSystem
{
public:
	static void DrawModel(const Model& model, const sm::mat4& mat);

}; // RenderSystem

}