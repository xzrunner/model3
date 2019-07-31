#include "node3/CompModelInst.h"

#include <model/Model.h>
#include <model/ModelInstance.h>
#include <model/SkeletalAnim.h>

namespace n3
{

const char* const CompModelInst::TYPE_NAME = "n3_model_inst";

CompModelInst::CompModelInst(const std::shared_ptr<model::Model>& model, int anim_idx)
{
	SetModel(model, anim_idx);
}

std::unique_ptr<n0::NodeComp> CompModelInst::Clone(const n0::SceneNode& node) const
{
	if (!m_inst) {
        return std::make_unique<CompModelInst>();
	}

    auto ret = std::make_unique<CompModelInst>(m_inst->GetModel(), m_inst->GetCurrAnimIndex());
    ret->GetModel()->SetModelExt(m_inst->GetModelExt()->Clone());
    return ret;

}

bool CompModelInst::Update()
{
	return m_inst ? m_inst->Update() : false;
}

void CompModelInst::SetModel(const std::shared_ptr<model::Model>& model, int anim_idx)
{
	m_inst = std::make_unique<model::ModelInstance>(model, anim_idx);
}

void CompModelInst::SetAnim(const std::string& anim_name)
{
	auto& model = m_inst->GetModel();
	if (!model->ext || model->ext->Type() != model::EXT_SKELETAL) {
		return;
	}

	auto sk_anim = static_cast<model::SkeletalAnim*>(model->ext.get());
	auto& anims = sk_anim->GetAnims();
	for (int i = 0, n = anims.size(); i < n; ++i) {
		if (anims[i]->name == anim_name) {
			m_inst->SetCurrAnimIndex(i);
			break;
		}
	}
}

}