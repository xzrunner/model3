#ifndef _MODEL3_SURFACE_H_
#define _MODEL3_ISURFACE_H_

#include <cu/cu_stl.h>

namespace m3 
{

class Surface 
{
public:
	virtual int GetVertexCount() const = 0;
	virtual int GetTriangleIndexCount() const = 0;
	virtual void GenerateVertices(int vertex_type, CU_VEC<float>& vertices) const = 0;
	virtual void GenerateTriangleIndices(CU_VEC<unsigned short>& indices) const = 0;
	virtual ~Surface() {}
};

}

#endif // _MODEL3_ISURFACE_H_