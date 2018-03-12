#pragma once

#include "node3/Model.h"

#include <node0/CompAsset.h>

#include <memory>

namespace n3
{

class CompMesh : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompMesh>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const {}

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<Model> m_model = nullptr;

}; // CompMesh

}