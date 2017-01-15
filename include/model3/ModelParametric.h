#ifndef _MODEL3_MODEL_PARAMETRIC_H_
#define _MODEL3_MODEL_PARAMETRIC_H_

#include "Model.h"

namespace m3
{

class Surface;
class AABB;

class ModelParametric : public Model
{
public:
	ModelParametric();
	ModelParametric(const Surface* surface, AABB& aabb);

	virtual const std::vector<Mesh>& GetAllMeshes() const {
		return m_meshes;
	}

	void AddMesh(const Mesh& mesh) {
		m_meshes.push_back(mesh);
	}

private:
	std::vector<Mesh> m_meshes;

}; // ModelParametric

}

#endif // _MODEL3_MODEL_PARAMETRIC_H_