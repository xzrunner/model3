#pragma once

#include <node0/CompAsset.h>

namespace model { struct SkinnedModelInstance; }

namespace n3
{

class CompAnim : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompAnim>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override {}

	void SetAnim(std::unique_ptr<model::SkinnedModelInstance>& model);
	const std::unique_ptr<model::SkinnedModelInstance>& GetModel() const;

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<model::SkinnedModelInstance> m_anim = nullptr;

}; // CompAnim

}