#pragma once

#include <node0/NodeComp.h>
#include <model/ModelInstance.h>

//#include <memory>

namespace n3
{

class CompModelInst : public n0::NodeComp
{
public:
	CompModelInst() = default;
	CompModelInst(const std::shared_ptr<model::Model>& model, int anim_idx);

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompModelInst>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	bool Update();

	std::unique_ptr<model::ModelInstance>& GetModel() { return m_inst; }
	const std::unique_ptr<model::ModelInstance>& GetModel() const { return m_inst; }
	void SetModel(const std::shared_ptr<model::Model>& model, int anim_idx);

	void SetAnim(const std::string& anim_name);

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<model::ModelInstance> m_inst = nullptr;

}; // CompModelInst

}