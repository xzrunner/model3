#include "node3/AABBSystem.h"
#include "node3/CompModel.h"

#include <node0/CompAsset.h>

namespace n3
{

sm::cube AABBSystem::GetBounding(const n0::CompAsset& casset)
{
	auto type = casset.AssetTypeID();
	if (type == n0::GetAssetUniqueTypeID<CompModel>())
	{
		return sm::cube(100, 100, 0);
	}
	else
	{
		return sm::cube(0, 0, 0);	
	}
}

}