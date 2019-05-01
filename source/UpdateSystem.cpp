#include "node3/UpdateSystem.h"
#include "node3/CompModel.h"
#include "node3/CompModelInst.h"
#include "node3/CompRigid.h"
#include "node3/CompCloth.h"
#include "node3/CompTransform.h"

#include <uniphysics/rigid/Body.h>
#include <node0/SceneNode.h>

namespace n3
{

bool UpdateSystem::Update(const n0::SceneNodePtr& node)
{
	if (!node || !node->HasSharedComp<n0::CompAsset>()) {
		return false;
	}

	bool dirty = false;

	auto& casset = node->GetSharedComp<n0::CompAsset>();
	auto asset_type = casset.AssetTypeID();
    // model
	if (asset_type == n0::GetAssetUniqueTypeID<CompModel>())
	{
		auto& cmodel = node->GetUniqueComp<CompModelInst>();
		if (cmodel.Update()) {
			dirty = true;
		}
	}

    // rigid
    if (node->HasUniqueComp<CompRigid>())
    {
        auto& crigid = node->GetUniqueComp<CompRigid>();
        auto pos = crigid.GetBody()->GetPosition();
        auto& ctrans = node->GetUniqueComp<CompTransform>();
        ctrans.SetPosition(pos);
        dirty = true;
    }
    // cloth
    if (node->HasUniqueComp<CompCloth>())
    {
        auto& ccloth = node->GetUniqueComp<CompCloth>();
        ccloth.UpdateRenderMesh();
        dirty = true;
    }

	return dirty;
}

}