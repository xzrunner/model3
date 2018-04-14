#pragma once

#include <model/Mesh.h>

#include <SM_Matrix.h>

#include <map>

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace pt3 { class AABB; }
namespace model { class Mesh; class Model; class Material; }

namespace n3
{

class AssimpHelper
{
public:
	static std::shared_ptr<model::Model> Load(const std::string& filepath, pt3::AABB& aabb);

private:
	static void LoadNode(const aiScene* scene, const aiNode* node, model::Model& model,
		const std::string& dir, pt3::AABB& aabb);

	static model::MeshPtr LoadMesh(const aiMesh* ai_mesh, const aiMaterial* ai_material,
		const std::string& dir, const sm::mat4& trans, pt3::AABB& aabb);

	static void LoadMaterial(const aiMesh* ai_mesh, const aiMaterial* ai_material, 
		model::Mesh& mesh, const std::string& dir);

}; // AssimpHelper

}