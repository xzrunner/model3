#ifndef _MODEL3_MODEL_H_
#define _MODEL3_MODEL_H_

#include "Mesh.h"

#include <CU_RefCountObj.h>

#include <vector>

namespace m3
{

class Model : public cu::RefCountObj
{
public:
	virtual const std::vector<Mesh>& GetAllMeshes() const = 0;
	virtual ~Model() {}
}; // Model

}

#endif // _MODEL3_MODEL_H_