#ifndef _NODE3_MODEL_H_
#define _NODE3_MODEL_H_

#include "node3/Mesh.h"

#include <cu/CU_RefCountObj.h>
#include <cu/uncopyable.h>

#include <rapidjson/document.h>

#include <vector>
#include <memory>

namespace n3
{

class Mesh;

class Model : private cu::Uncopyable
{
public:
	virtual const char* Type() const = 0;

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const = 0;
	virtual void LoadFromJson(const rapidjson::Value& val) = 0;

	const std::vector<MeshPtr>& GetAllMeshes() const { return m_meshes; }

	void AddMesh(const MeshPtr& mesh) { m_meshes.push_back(mesh); }

protected:
	std::vector<MeshPtr> m_meshes;
	
}; // Model

}

#endif // _NODE3_MODEL_H_