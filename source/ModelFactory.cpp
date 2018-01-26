#include "node3/ModelFactory.h"
#include "node3/ModelObj.h"
#include "node3/ModelParametric.h"

namespace n3
{

std::shared_ptr<Model> ModelFactory::Create(const std::string& type)
{
	if (type == ModelObj::TYPE_NAME) {
//		return std::make_shared<ModelObj>();
		return nullptr;
	} else if (type == ModelParametric::TYPE_NAME) {
		return std::make_shared<ModelParametric>();
	} else {
		return nullptr;
	}
}

}