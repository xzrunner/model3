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
	int      tex;	

}; // Material

}

#endif // _MODEL3_MATERIAL_H_