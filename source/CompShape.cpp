#include "node3/CompShape.h"

#include <guard/check.h>
#include <geoshape/Shape3D.h>

namespace n3
{

const char* const CompShape::TYPE_NAME = "n3_shape";

CompShape::CompShape(const std::shared_ptr<gs::Shape3D>& shape)
	: m_shape(shape)
{
}

}