#ifndef _MODEL3_MATERIAL_H_
#define _MODEL3_MATERIAL_H_

#include <SM_Vector.h>

namespace m3
{

class Material
{
public:
	sm::vec3 ambient;
	sm::vec3 diffuse;
	sm::vec3 specular;
	float    shininess;
	void*    texture;

public:
	Material() 
		: ambient(0.04f, 0.04f, 0.04f)
		, diffuse(1, 1, 1)
		, specular(1, 1, 1)
		, shininess(50)
		, texture(nullptr)
	{}

}; // Material

}

#endif // _MODEL3_MATERIAL_H_