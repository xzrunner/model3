#include "node3/UpdateSystem.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"

#include <node0/SceneNode.h>

namespace n3
{

bool UpdateSystem::Update(const n0::SceneNodePtr& node)
{
	if (!node) {
		return false;
	}

	bool dirty = false;

	auto& casset = node->GetSharedComp<n0::CompAsset>();
	auto asset_type = casset.AssetTypeID();
	if (asset_type == n0::GetAssetUniqueTypeID<n3::CompModel>())
	{
		auto& cmodel = node->GetUniqueComp<n3::CompModelInst>();
		if (cmodel.Update()) {
			dirty = true;
		}
	}

	return dirty;
}

}