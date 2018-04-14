#pragma once

#include <node0/CompAsset.h>

#include <memory>

namespace model { class Model; }

namespace n3
{

class CompModel : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompModel>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const {}
	virtual sm::rect GetBounding() const;

	void SetModel(const std::shared_ptr<model::Model>& model) { m_model = model; }
	const std::shared_ptr<model::Model>& GetModel() const { return m_model; }
		
	static const char* const TYPE_NAME;

private:
	std::shared_ptr<model::Model> m_model = nullptr;

}; // CompModel

}