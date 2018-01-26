#ifndef _NODE3_MODEL_H_
#define _NODE3_MODEL_H_

#include <cu/CU_RefCountObj.h>
#include <cu/uncopyable.h>

#include <rapidjson/document.h>

#include <vector>

namespace n3
{

class Mesh;

class Model : public cu::RefCountObj, private cu::Uncopyable
{
public:
	virtual ~Model();

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const = 0;
	virtual void LoadFromJson(const rapidjson::Value& val) = 0;

	const std::vector<Mesh*>& GetAllMeshes() const { return m_meshes; }

	void AddMesh(Mesh* mesh);

protected:
	std::vector<Mesh*> m_meshes;
	
}; // Model

}

#endif // _NODE3_MODEL_H_