#include "node3/CompLight.h"

#include <painting3/Light.h>
#include <js/RTTR.h>

namespace n3
{

const char* const CompLight::TYPE_NAME = "n3_light";

std::unique_ptr<n0::NodeComp> CompLight::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompLight>();
    if (!m_light) {
        return comp;
    }

    auto type = m_light->get_type();
    auto ctor = type.get_constructor();
    auto var = ctor.invoke();
    auto dst = var.get_value<std::shared_ptr<pt3::Light>>();
    comp->SetLight(dst);

    for (auto& prop : type.get_properties())
    {
        if (prop.get_metadata(js::RTTR::NoSerializeTag())) {
            continue;
        }

        rttr::variant prop_value = prop.get_value(m_light);
        if (!prop_value) {
            continue;
        }

        prop.set_value(dst, prop_value);
    }

	return comp;
}

}