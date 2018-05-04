#pragma once

#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace model { class Model; }

namespace n3
{

class RenderParams
{
public:
	sm::mat4 mt;

public:
	RenderParams(const sm::mat4& mt) 
		: mt(mt) {}

}; // RenderParams

class RenderSystem
{
public:
	static void Draw(const n0::SceneNodePtr& node, const sm::mat4& mt);

private:
	static void DrawModel(const model::Model& model, const sm::mat4& mat);

}; // RenderSystem

}