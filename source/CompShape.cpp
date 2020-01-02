#include "node3/CompShape.h"

namespace n3
{

std::unique_ptr<n0::NodeComp>
CompShape::Clone(const n0::SceneNode& node) const
{
    auto comp = std::make_unique<CompShape>();
    comp->SetShapes(m_shapes);
    return comp;
}

}