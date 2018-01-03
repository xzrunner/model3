#pragma once

#include "node3/IModel.h"
#include "node3/AABB.h"

#include <SM_Vector.h>
#include <SM_Matrix.h>

namespace n3
{

class INode
{
public:

	virtual bool Update() = 0;

	const ModelPtr& GetModel() const { return m_model; }

	const sm::mat4& GetMat() const { return m_mat; }

private:
	struct SRT
	{
		sm::vec3 position;
		sm::vec3 angle;	// todo
		sm::vec3 scale;
	};

protected:
	ModelPtr m_model = nullptr;

	SRT      m_srt;
	sm::mat4 m_mat;

	AABB m_aabb;

}; // INode

typedef std::shared_ptr<INode>       NodePtr;
typedef std::shared_ptr<const INode> NodeConstPtr;

}