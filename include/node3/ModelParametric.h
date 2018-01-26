#ifndef _NODE3_MODEL_PARAMETRIC_H_
#define _NODE3_MODEL_PARAMETRIC_H_

#include "node3/Model.h"
#include "node3/Mesh.h"

namespace n3
{

class Surface;
class AABB;

class ModelParametric : public Model
{
public:
	ModelParametric();
	ModelParametric(const Surface* surface, AABB& aabb);

	virtual const char* Type() const override { return TYPE_NAME; }

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(const rapidjson::Value& val) override;

	static const char* const TYPE_NAME;

private:
	static MeshPtr CreateMeshFromSurface(const Surface* surface, AABB& aabb);

}; // ModelParametric

}

#endif // _NODE3_MODEL_PARAMETRIC_H_