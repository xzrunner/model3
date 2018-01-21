#pragma once

#include "node3/NodeComponent.h"
#include "node3/Model.h"

namespace n3
{

class CompModel : public NodeComponent
{
public:
	CompModel(SceneNode* entity)
		: NodeComponent(entity)
	{}

	void SetModel(const n3::Model* model) {
		m_model = model;
	}

	const n3::Model& GetModel() const {
		assert(m_model);
		return *m_model;
	}
		
private:
	const n3::Model* m_model = nullptr;

}; // CompModel

}