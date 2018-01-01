#include "model3/AssimpHelper.h"
#include "model3/Model.h"
#include "model3/Mesh.h"
#include "model3/Material.h"
#include "model3/m3_typedef.h"
#include "model3/ResourceAPI.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace m3
{

// default pp steps
unsigned int ppsteps = aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
	aiProcess_JoinIdenticalVertices    | // join identical vertices/ optimize indexing
	aiProcess_ValidateDataStructure    | // perform a full validation of the loader's output
	aiProcess_ImproveCacheLocality     | // improve the cache locality of the output vertices
	aiProcess_RemoveRedundantMaterials | // remove redundant materials
	aiProcess_FindDegenerates          | // remove degenerated polygons from the import
	aiProcess_FindInvalidData          | // detect invalid model data, such as invalid normal vectors
	aiProcess_GenUVCoords              | // convert spherical, cylindrical, box and planar mapping to proper UVs
	aiProcess_TransformUVCoords        | // preprocess UV transformations (scaling, translation ...)
	aiProcess_FindInstances            | // search for instanced meshes and remove them by references to one master
	aiProcess_LimitBoneWeights         | // limit bone weights to 4 per vertex
	aiProcess_OptimizeMeshes		   | // join small meshes, if possible;
	aiProcess_SplitByBoneCount         | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
	0;

Model* AssimpHelper::Load(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath.c_str(),
		ppsteps | /* configurable pp steps */
		aiProcess_GenSmoothNormals		   | // generate smooth normal vectors if not existing
		aiProcess_SplitLargeMeshes         | // split large, unrenderable meshes into submeshes
		aiProcess_Triangulate			   | // triangulate polygons with more than 3 edges
		aiProcess_ConvertToLeftHanded	   | // convert everything to D3D left handed space
		aiProcess_SortByPType                // make 'clean' meshes which consist of a single typ of primitives
		);

	if (!scene) {
		return NULL;
	}

	std::string dir = filepath;
	int pos = dir.find_last_of('/');
	if (pos != std::string::npos) {
		dir = dir.substr(0, pos);
	} else {
		dir = "";
	}

	Model* model = new Model;
	LoadNode(scene, scene->mRootNode, *model, dir);

	// todo: load lights and cameras

	return model;
}

void AssimpHelper::LoadNode(const aiScene* ai_scene, const aiNode* ai_node, 
							Model& model, const std::string& dir)
{
	if (ai_node->mNumChildren) 
	{
		for (int i = 0; i < ai_node->mNumChildren; ++i) {
			LoadNode(ai_scene, ai_node->mChildren[i], model, dir);
		}
	} 
	else 
	{
		if (ai_node->mNumMeshes) 
		{
			for (int i = 0; i < ai_node->mNumMeshes; ++i) 
			{
				const aiMesh* mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
				const aiMaterial* material = ai_scene->mMaterials[mesh->mMaterialIndex];

				m3::Mesh* m3_mesh = LoadMesh(mesh, material, dir);
				model.AddMesh(m3_mesh);
				m3_mesh->RemoveReference();
			}
		}
	}
}

Mesh* AssimpHelper::LoadMesh(const aiMesh* ai_mesh, const aiMaterial* ai_material, const std::string& dir)
{
	Mesh* mesh = new Mesh;

	LoadMaterial(ai_mesh, ai_material, *mesh, dir);

	int vertex_type = 0;
	int floats_per_vertex = 3;
	bool has_normal = ai_mesh->HasNormals();
	if (has_normal) {
		floats_per_vertex += 3;
		vertex_type |= m3::VERTEX_FLAG_NORMALS;
	}
	bool has_texcoord = ai_mesh->HasTextureCoords(0);
	if (has_texcoord) {
		floats_per_vertex += 2;
		vertex_type |= m3::VERTEX_FLAG_TEXCOORDS;
	}

	CU_VEC<float> vertices;
	vertices.reserve(floats_per_vertex * ai_mesh->mNumVertices);
	for (int i = 0; i < ai_mesh->mNumVertices; ++i) 
	{
		const aiVector3D& p = ai_mesh->mVertices[i];
		vertices.push_back(p.x);
		vertices.push_back(p.y);
		vertices.push_back(p.z);
		if (has_normal) {
			const aiVector3D& n = ai_mesh->mNormals[i];
			vertices.push_back(n.x);
			vertices.push_back(n.y);
			vertices.push_back(n.z);
		}
		if (has_texcoord) {
			const aiVector3D& t = ai_mesh->mTextureCoords[0][i];
			vertices.push_back(t.x);
			vertices.push_back(t.y);
		}
	}

	int count = 0;
	for (int i = 0; i < ai_mesh->mNumFaces; ++i) {
		const aiFace& face = ai_mesh->mFaces[i];
		count += face.mNumIndices;
	}
	CU_VEC<uint16_t> indices;
	indices.reserve(count);

	for (int i = 0; i < ai_mesh->mNumFaces; ++i) {
		const aiFace& face = ai_mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}

	mesh->SetRenderBuffer(vertex_type, vertices, indices);

	return mesh;
}

void AssimpHelper::LoadMaterial(const aiMesh* ai_mesh, const aiMaterial* ai_material, Mesh& mesh, const std::string& dir)
{
	m3::Material material;

	aiColor4D col;

	if (aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_DIFFUSE, &col) == AI_SUCCESS) {
		material.diffuse.x = col.r;
		material.diffuse.y = col.g;
		material.diffuse.z = col.b;
	} else {
		material.diffuse.x = material.diffuse.y = material.diffuse.z = 1;
	}

	if (aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_SPECULAR, &col) == AI_SUCCESS) {
		material.specular.x = col.r;
		material.specular.y = col.g;
		material.specular.z = col.b;
	} else {
		material.specular.x = material.specular.y = material.specular.z = 1;
	}

	if (aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_AMBIENT, &col) == AI_SUCCESS) {
		material.ambient.x = col.r;
		material.ambient.y = col.g;
		material.ambient.z = col.b;
	} else {
		material.ambient.x = material.ambient.y = material.ambient.z = 0.04f;
	}
	material.shininess = 50;

	material.texture = nullptr;
	if (ai_mesh->mTextureCoords[0]) 
	{
		aiString path;
		if (aiGetMaterialString(ai_material, AI_MATKEY_TEXTURE_DIFFUSE(0), &path) == AI_SUCCESS) 
		{
 			std::string img_path = dir + '/' + path.data;
			material.texture = ResourceAPI::CreateImg(img_path);
		}
	}

	mesh.SetMaterial(material);
}

}