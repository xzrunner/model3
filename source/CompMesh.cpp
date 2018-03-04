#include "node3/CompMesh.h"

namespace n3
{

const char* const CompMesh::TYPE_NAME = "n3_mesh";

std::unique_ptr<n0::NodeComponent> CompMesh::Clone() const
{
	auto comp = std::make_unique<CompMesh>();
	// todo
//	comp->m_model = m_model->Clone();
	return comp;
}

}