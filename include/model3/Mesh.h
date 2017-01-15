#ifndef _MODEL3_MESH_H_
#define _MODEL3_MESH_H_

#include "Material.h"

#include <vector>

#include <stdint.h>

namespace m3
{

class Mesh
{
public:
	int vertex_type;

	std::vector<sm::vec3> vertices;
	std::vector<sm::vec2> texcoords;
	std::vector<sm::vec3> normals;

	std::vector<uint16_t> indices;

	Material material;

}; // Mesh

}

#endif // _MODEL3_MESH_H_