#pragma once

#include <node0/CompAsset.h>

namespace gs { class Shape3D; }

namespace n3
{

class CompShape : public n0::CompAsset
{
public:
    CompShape() {}
	CompShape(const std::shared_ptr<gs::Shape3D>& shape);

    virtual const char* Type() const override { return TYPE_NAME; }

    virtual n0::AssetID AssetTypeID() const override {
        return n0::GetAssetUniqueTypeID<CompShape>();
    }
    virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
        bool inverse = false) const override {}

	void SetShape(const std::shared_ptr<gs::Shape3D>& shape) { m_shape = shape; }
	auto& GetShape() const { return m_shape; }

	static const char* const TYPE_NAME;

private:
	std::shared_ptr<gs::Shape3D> m_shape = nullptr;

}; // CompShape

}