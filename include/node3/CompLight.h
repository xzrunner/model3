#pragma once

#include <node0/NodeComp.h>

namespace pt3 { class Light; }

namespace n3
{

class CompLight : public n0::NodeComp
{
public:
    virtual const char* Type() const override { return TYPE_NAME; }
    virtual n0::CompID TypeID() const override {
        return n0::GetCompTypeID<CompLight>();
    }
    virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

    void SetLight(const std::shared_ptr<pt3::Light>& light) { m_light = light; }
    auto& GetLight() const { return m_light; }

    static const char* const TYPE_NAME;

private:
    // fixme: use unique_ptr
	std::shared_ptr<pt3::Light> m_light = nullptr;

}; // CompLight

}