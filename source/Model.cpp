#include "model3/Model.h"
#include "model3/Mesh.h"

#include <algorithm>

namespace m3
{

Model::~Model()
{
	for_each(m_meshes.begin(), m_meshes.end(), cu::RemoveRefFunctor<Mesh>());
}

void Model::AddMesh(Mesh* mesh)
{
	mesh->AddReference();
	m_meshes.push_back(mesh);
}

}