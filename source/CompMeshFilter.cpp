#include "node3/CompMeshFilter.h"

#include <model/SurfaceLoader.h>

namespace n3
{

const char* const CompMeshFilter::TYPE_NAME = "n3_mesh_filter";

std::unique_ptr<n0::NodeComp> CompMeshFilter::Clone(const n0::SceneNode& node) const
{
    auto comp = std::make_unique<CompMeshFilter>();
    comp->SetMesh(m_name);
    return comp;
}

void CompMeshFilter::SetMesh(const std::string& name)
{
    if (m_name == name) {
        return;
    }

    m_aabb.MakeEmpty();
    m_mesh = model::SurfaceLoader::CreateMesh(name, m_aabb);

    m_name = name;
}

}