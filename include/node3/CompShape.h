#pragma once

#include <node0/NodeComp.h>

#include <vector>

namespace gs { class Shape3D; }

namespace n3
{

class CompShape : public n0::NodeComp
{
public:
    virtual const char* Type() const override { return TYPE_NAME; }
    virtual n0::CompID TypeID() const override {
        return n0::GetCompTypeID<CompShape>();
    }
    virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

    void SetShapes(const std::vector<std::shared_ptr<gs::Shape3D>>& shapes) { m_shapes = shapes; }
    auto& GetShapes() const { return m_shapes; }

    static constexpr char* const TYPE_NAME = "n3_shape";

private:
	std::vector<std::shared_ptr<gs::Shape3D>> m_shapes;

}; // CompShape

}