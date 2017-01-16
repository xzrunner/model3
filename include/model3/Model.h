#ifndef _MODEL3_MODEL_H_
#define _MODEL3_MODEL_H_

#include <CU_RefCountObj.h>
#include <CU_Uncopyable.h>

#include <vector>

namespace m3
{

class Mesh;

class Model : public cu::RefCountObj, private cu::Uncopyable
{
public:
	virtual ~Model();

	const std::vector<Mesh*>& GetAllMeshes() const { return m_meshes; }

	void AddMesh(Mesh* mesh);

protected:
	std::vector<Mesh*> m_meshes;
	
}; // Model

}

#endif // _MODEL3_MODEL_H_