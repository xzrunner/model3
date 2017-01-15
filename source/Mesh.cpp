#include "Mesh.h"

#include <shaderlab/RenderBuffer.h>
#include <shaderlab/RenderLayout.h>

namespace m3
{

Mesh::Mesh()
	: m_vb(NULL)
	, m_ib(NULL)
	, m_layout(NULL)
	, m_index_count(0)
{
}

Mesh::~Mesh()
{
	if (m_vb) m_vb->RemoveReference();
	if (m_ib) m_ib->RemoveReference();
	if (m_layout) m_layout->RemoveReference();
}

void Mesh::SetRenderBuffer(sl::RenderBuffer* vb, sl::RenderBuffer* ib)
{
	cu::RefCountObjAssign(m_vb, vb);
	cu::RefCountObjAssign(m_ib, ib);
}

void Mesh::SetMaterial(const sm::vec3& ambient, const sm::vec3& diffuse, const sm::vec3& specular)
{
	m_material.ambient  = ambient;
	m_material.diffuse  = diffuse;
	m_material.specular = specular;
}

}