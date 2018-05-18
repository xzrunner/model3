#include "node3/CompAnim.h"

#include <model/SkinnedModel.h>

namespace n3
{

const char* const CompAnim::TYPE_NAME = "n3_anim";

void CompAnim::SetAnim(std::unique_ptr<model::SkinnedModelInstance>& model)
{
	m_anim = std::move(model);
}

const std::unique_ptr<model::SkinnedModelInstance>& CompAnim::GetModel() const
{
	return m_anim;
}

}