#pragma once

#include "node3/NodeComponent.h"

#include <memory>

namespace n3
{

class Model;

class CompModel : public NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(const rapidjson::Value& val) override;

	void SetModel(const std::shared_ptr<Model>& model) { m_model = model; }
	const std::shared_ptr<Model>& GetModel() const { return m_model; }
		
	static const char* const TYPE_NAME;

private:
	std::shared_ptr<Model> m_model = nullptr;

}; // CompModel

}