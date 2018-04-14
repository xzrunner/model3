#include "node3/CompModel.h"

#include <model/ModelFactory.h>
#include <model/Model.h>

namespace n3
{

const char* const CompModel::TYPE_NAME = "n3_model";

//std::unique_ptr<n0::NodeComponent> CompModel::Clone() const
//{
//	auto comp = std::make_unique<CompModel>();
//	// todo
////	comp->m_model = m_model->Clone();
//	return comp;
//}

sm::rect CompModel::GetBounding() const
{
	return sm::rect(100, 100);
}

}