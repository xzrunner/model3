#pragma once

#include <node0/NodeComp.h>
#include <model/Model.h>

namespace n3
{

class CompMeshFilter : public n0::NodeComp
{
public:
    virtual const char* Type() const override { return TYPE_NAME; }
    virtual n0::CompID TypeID() const override {
        return n0::GetCompTypeID<CompMeshFilter>();
    }
    virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

    void  SetMesh(const std::string& name);
    auto& GetMesh() const { return m_mesh; }

    auto& GetAABB() const { return m_aabb; }

    auto& GetMeshName() const { return m_name; }

    static const char* const TYPE_NAME;

private:
    std::string m_name;

    std::unique_ptr<model::Model::Mesh> m_mesh = nullptr;

    sm::cube m_aabb;

}; // CompMeshFilter

}