#ifndef _NODE3_ASSIMP_HELPER_H_
#define _NODE3_ASSIMP_HELPER_H_

#include "node3/Mesh.h"

#include <SM_Matrix.h>

#include <map>

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace pt3 { class AABB; }

namespace n3
{

class Mesh;
class Model;
class Material;

class AssimpHelper
{
public:
	static std::shared_ptr<Model> Load(const std::string& filepath, pt3::AABB& aabb);

private:
	static void LoadNode(const aiScene* scene, const aiNode* node, Model& model, 
		const std::string& dir, pt3::AABB& aabb);

	static MeshPtr LoadMesh(const aiMesh* ai_mesh, const aiMaterial* ai_material, 
		const std::string& dir, const sm::mat4& trans, pt3::AABB& aabb);

	static void LoadMaterial(const aiMesh* ai_mesh, const aiMaterial* ai_material, 
		Mesh& mesh, const std::string& dir);

}; // AssimpHelper

}

#endif // _NODE3_ASSIMP_HELPER_H_