#ifndef _NODE3_MODEL_PARAMETRIC_H_
#define _NODE3_MODEL_PARAMETRIC_H_

#include "Model.h"

namespace n3
{

class Surface;
class AABB;

class ModelParametric : public Model
{
public:
	ModelParametric();
	ModelParametric(const Surface* surface, AABB& aabb);

}; // ModelParametric

}

#endif // _NODE3_MODEL_PARAMETRIC_H_