#include "node3/CompRigid.h"

#include <uniphysics/rigid/Body.h>

namespace n3
{

const char* const CompRigid::TYPE_NAME = "n3_rigid";

CompRigid::~CompRigid()
{
}

std::unique_ptr<n0::NodeComp> CompRigid::Clone(const n0::SceneNode& node) const
{
    return nullptr;
}

}