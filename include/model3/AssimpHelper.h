#ifndef _MODEL3_ASSIMP_HELPER_H_
#define _MODEL3_ASSIMP_HELPER_H_

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

#include <map>

namespace m3
{

class Model;
class Mesh;
class Material;

class AssimpHelper
{
public:
	static Model* Load(const std::string& filepath);

private:
	static void LoadNode(const aiScene* scene, const aiNode* node, Model& model, const std::string& dir);

	static Mesh* LoadMesh(const aiMesh* ai_mesh, const aiMaterial* ai_material, const std::string& dir);

	static void LoadMaterial(const aiMesh* ai_mesh, const aiMaterial* ai_material, Mesh& mesh, const std::string& dir);

}; // AssimpHelper

}

#endif // _MODEL3_ASSIMP_HELPER_H_