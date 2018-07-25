#pragma once

#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace ur { class Shader; }
namespace model { struct Model; class ModelInstance; }

namespace n3
{

class RenderParams
{
public:
	enum DrawType
	{
		DRAW_MESH = 0,
		DRAW_BORDER_MESH,
	};

public:
	sm::mat4 mt;

	DrawType type = DRAW_MESH;

}; // RenderParams

class RenderSystem
{
public:


public:
	static void Draw(const n0::SceneNodePtr& node, const RenderParams& params);

private:
	static void DrawModel(const model::ModelInstance& model, const RenderParams& params);

	static void DrawMesh(const model::Model& model, const RenderParams& params);

	static void DrawMorphAnim(const model::Model& model, const RenderParams& params);

	static void DrawSkeletalNode(const model::ModelInstance& model, int node_idx, const RenderParams& params);
	static void DrawSkeletalNodeDebug(const model::ModelInstance& model, int node_idx, const RenderParams& params);

	static void DrawBSP(const model::Model& model, const RenderParams& params);

}; // RenderSystem

}