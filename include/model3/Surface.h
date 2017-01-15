#ifndef _MODEL3_SURFACE_H_
#define _MODEL3_ISURFACE_H_

#include <vector>

namespace m3 
{

enum VertexFlags 
{
    VertexFlagsNormals = 1 << 0,
    VertexFlagsTexCoords = 1 << 1,
};

class Surface 
{
public:
	virtual int GetVertexCount() const = 0;
	virtual int GetTriangleIndexCount() const = 0;
	virtual void GenerateVertices(std::vector<float>& vertices,
		unsigned char flags = 0) const = 0;
	virtual void GenerateTriangleIndices(std::vector<unsigned short>& indices) const = 0;
	virtual ~Surface() {}
};

}

#endif // _MODEL3_ISURFACE_H_