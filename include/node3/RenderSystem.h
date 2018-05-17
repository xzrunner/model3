#pragma once

#include <SM_Matrix.h>
#include <node0/typedef.h>
#include <model/Scene.h>

namespace ur { class Shader; }

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
	static void DrawModel(const model::Scene& scene, const sm::mat4& mat);
	static void DrawNode(const model::Scene& scene, const model::Scene::Node& node, const sm::mat4& mat);

}; // RenderSystem

}