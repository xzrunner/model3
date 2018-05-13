#pragma once

#include <cu/cu_macro.h>
#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace model { class Model; }
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
	void Draw(const n0::SceneNodePtr& node, const sm::mat4& mt);

private:
	void DrawModel(const model::Model& model, const sm::mat4& mat);

private:
	ur::Shader* m_model_shader;

	CU_SINGLETON_DECLARATION(RenderSystem)

}; // RenderSystem

}