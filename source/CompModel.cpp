#include "node3/CompModel.h"

#include <model/Model.h>
#include <painting0/Material.h>
#include <painting3/MaterialMgr.h>

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

void CompModel::SetModel(const std::shared_ptr<model::Model>& model)
{
    m_model = model;
    InitMaterials();
}

void CompModel::InitMaterials()
{
    m_materials.clear();

    if (!m_model) {
        return;
    }

    typedef pt3::MaterialMgr::PhongUniforms UNIFORMS;

    m_materials.resize(m_model->materials.size());
    for (size_t i = 0, n = m_model->materials.size(); i < n; ++i)
    {
        auto& src = m_model->materials[i];
        auto& dst = m_materials[i];

        dst.AddVar(UNIFORMS::ambient.name,     pt0::RenderVariant(src->ambient));
        dst.AddVar(UNIFORMS::diffuse.name,     pt0::RenderVariant(src->diffuse));
        dst.AddVar(UNIFORMS::specular.name,    pt0::RenderVariant(src->specular));
        dst.AddVar(UNIFORMS::shininess.name,   pt0::RenderVariant(src->shininess));

        ur::Texture* tex = nullptr;
        if (src->diffuse_tex >= 0) {
            tex = m_model->textures[src->diffuse_tex].second.get();
            if (tex) {
                dst.AddVar(UNIFORMS::diffuse_tex.name, pt0::RenderVariant(tex));
            }
        }
    }

    
}

}