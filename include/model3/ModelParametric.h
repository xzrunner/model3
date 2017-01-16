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

}; // ModelParametric

}

#endif // _MODEL3_MODEL_PARAMETRIC_H_