#pragma once

#include <node0/NodeComp.h>
#include <model/Model.h>

namespace up
{
namespace cloth
{
    class Factory;
    class Solver;
    class Fabric;
    class Cloth;
    class ClothMeshData;
}
}

namespace n3
{

class CompCloth : public n0::NodeComp
{
public:
    virtual const char* Type() const override { return TYPE_NAME; }
    virtual n0::CompID TypeID() const override {
        return n0::GetCompTypeID<CompCloth>();
    }
    virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

    void BuildFromClothMesh(const ur::Device& dev, const sm::vec3& center,
        up::cloth::Factory& factory, up::cloth::ClothMeshData& cloth_mesh);

    auto GetSolver() { return m_solver; }
    auto GetFabric() { return m_fabric; }
    auto& GetCloth() { return m_cloth; }

    auto& GetRenderMesh() const { return m_render_mesh; }
    void UpdateRenderMesh();

    static const char* const TYPE_NAME;

private:
    void BuildRenderMesh(const ur::Device& dev,
        model::Model::Mesh& dst, const up::cloth::ClothMeshData& src);

private:
    std::shared_ptr<up::cloth::Solver> m_solver = nullptr;

    std::shared_ptr<up::cloth::Fabric> m_fabric = nullptr;
    std::shared_ptr<up::cloth::Cloth>  m_cloth  = nullptr;

    std::unique_ptr<model::Model::Mesh> m_render_mesh = nullptr;

    std::vector<uint16_t> m_indices;

}; // CompCloth

}