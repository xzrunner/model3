#pragma once

#include <node0/CompAsset.h>

#include <vector>

namespace gs { class Shape3D; }

namespace n3
{

class CompShape : public n0::CompAsset
{
public:
    CompShape() {}

    virtual const char* Type() const override { return TYPE_NAME; }

    virtual n0::AssetID AssetTypeID() const override {
        return n0::GetAssetUniqueTypeID<CompShape>();
    }
    virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
        bool inverse = false) const override {}

    void SetShapes(const std::vector<std::shared_ptr<gs::Shape3D>>& shapes) { m_shapes = shapes; }
    auto& GetShapes() const { return m_shapes; }

	static const char* const TYPE_NAME;

private:
	std::vector<std::shared_ptr<gs::Shape3D>> m_shapes;

}; // CompShape

}