#pragma once

#include <node0/CompAsset.h>
#include <painting0/Material.h>

#include <memory>
#include <vector>

namespace model { struct Model; }

namespace n3
{

class CompModel : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompModel>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override {}

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }

    void SetModel(const std::shared_ptr<model::Model>& model);
	const std::shared_ptr<model::Model>& GetModel() const { return m_model; }

    auto& GetAllMaterials() const { return m_materials; }

	static const char* const TYPE_NAME;

private:
    void InitMaterials();

private:
	std::string m_filepath;

	std::shared_ptr<model::Model> m_model = nullptr;

    std::vector<pt0::Material> m_materials;

}; // CompModel

}