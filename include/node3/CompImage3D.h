#pragma once

#include <node0/CompAsset.h>
#include <painting3/Texture3D.h>

namespace n3
{

class CompImage3D : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompImage3D>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override {}

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }

	void SetTexture(const std::shared_ptr<pt3::Texture3D>& tex) { m_tex = tex; }
	const std::shared_ptr<pt3::Texture3D>& GetTexture() const { return m_tex; }

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;

	std::shared_ptr<pt3::Texture3D> m_tex = nullptr;

}; // CompImage3D

}