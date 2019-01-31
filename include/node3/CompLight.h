#pragma once

#include <node0/CompAsset.h>

namespace pt3 { class Light; }

namespace n3
{

class CompLight : public n0::CompAsset
{
public:
    virtual const char* Type() const override { return TYPE_NAME; }

    virtual n0::AssetID AssetTypeID() const override {
        return n0::GetAssetUniqueTypeID<CompLight>();
    }
    virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
        bool inverse = false) const override {}

    void SetLight(const std::shared_ptr<pt3::Light>& light) { m_light = light; }
    auto& GetLight() const { return m_light; }

    static const char* const TYPE_NAME;

private:
    // fixme: use unique_ptr
	std::shared_ptr<pt3::Light> m_light = nullptr;

}; // CompLight

}