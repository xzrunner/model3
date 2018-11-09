#include "node3/AABBSystem.h"
#include "node3/CompModel.h"
#include "node3/CompAnim.h"

#include <model/Model.h>

namespace n3
{

sm::cube AABBSystem::GetBounding(const n0::CompAsset& casset)
{
	sm::cube cube;

	auto type = casset.AssetTypeID();
	if (type == n0::GetAssetUniqueTypeID<CompModel>())
	{
		auto& cmodel = static_cast<const CompModel&>(casset);
		cube = cmodel.GetModel()->aabb;
	}

	return cube;
}

}