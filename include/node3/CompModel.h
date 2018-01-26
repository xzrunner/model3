#pragma once

#include "node3/NodeComponent.h"
#include "node3/Model.h"

namespace n3
{

class CompModel : public NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(const rapidjson::Value& val) override;

	void SetModel(const n3::Model* model) {
		m_model = model;
	}

	const n3::Model& GetModel() const {
		assert(m_model);
		return *m_model;
	}
		
	static const char* const TYPE_NAME;

private:
	const n3::Model* m_model = nullptr;

}; // CompModel

}