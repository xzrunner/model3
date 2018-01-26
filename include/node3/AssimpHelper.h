#ifndef _NODE3_ASSIMP_HELPER_H_
#define _NODE3_ASSIMP_HELPER_H_

#include "node3/Mesh.h"

#include <SM_Matrix.h>

#include <map>

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace n3
{

class Mesh;
class Model;
class Material;
class AABB;

class AssimpHelper
{
public:
	static std::shared_ptr<Model> Load(const std::string& filepath, AABB& aabb);

private:
	static void LoadNode(const aiScene* scene, const aiNode* node, Model& model, 
		const std::string& dir, AABB& aabb);

	static MeshPtr LoadMesh(const aiMesh* ai_mesh, const aiMaterial* ai_material, 
		const std::string& dir, const sm::mat4& trans, AABB& aabb);

	static void LoadMaterial(const aiMesh* ai_mesh, const aiMaterial* ai_material, 
		Mesh& mesh, const std::string& dir);

}; // AssimpHelper

}

#endif // _NODE3_ASSIMP_HELPER_H_