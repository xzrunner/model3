#include "node3/CompModelInst.h"

#include <model/ModelInstance.h>

namespace n3
{

const char* const CompModelInst::TYPE_NAME = "n3_model_inst";

CompModelInst::CompModelInst(const std::shared_ptr<model::Model>& model, int anim_idx)
{
	SetModel(model, anim_idx);
}

std::unique_ptr<n0::NodeUniqueComp> CompModelInst::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompModelInst>(m_inst->model, m_inst->curr_anim_index);
	return comp;
}

bool CompModelInst::Update()
{
	return m_inst->Update();
}

void CompModelInst::SetModel(const std::shared_ptr<model::Model>& model, int anim_idx)
{
	m_inst = std::make_unique<model::ModelInstance>(model, anim_idx);
}

}