#include "node3/CompCloth.h"

#include <uniphysics/cloth/ClothMeshData.h>
#include <uniphysics/cloth/Factory.h>
#include <uniphysics/cloth/Cloth.h>
#include <uniphysics/cloth/Solver.h>
#include <uniphysics/cloth/nv/Cloth.h> // fixme
#include <uniphysics/cloth/nv/Fabric.h> // fixme

// fixme
#include <NvCloth/Allocator.h>
#include <NvCloth/PhaseConfig.h>
#include <NvCloth/Fabric.h>
#include <NvCloth/Cloth.h>
#include <NvClothExt/ClothMeshDesc.h>
#include <foundation/PxStrideIterator.h>
#include <foundation/PxVec4.h>
#include <unirender/VertexArray.h>
#include <unirender/IndexBuffer.h>
#include <unirender/VertexBuffer.h>
#include <unirender/Device.h>
#include <unirender/ComponentDataType.h>
#include <unirender/VertexBufferAttribute.h>

namespace
{

struct Vertex
{
    sm::vec3 position;
    sm::vec3 normal;
};

template <typename T>
void gather_indices(std::vector<uint16_t>& indices,
                    const nv::cloth::BoundedData& triangles,
                    const nv::cloth::BoundedData& quads)
{
	physx::PxStrideIterator<const T> tIt, qIt;

	indices.reserve(triangles.count * 3 + quads.count * 6);

	tIt = physx::PxMakeIterator(reinterpret_cast<const T*>(triangles.data), triangles.stride);
	for (physx::PxU32 i = 0; i < triangles.count; ++i, ++tIt)
	{
		indices.push_back(static_cast<uint16_t>(tIt.ptr()[0]));
		indices.push_back(static_cast<uint16_t>(tIt.ptr()[1]));
		indices.push_back(static_cast<uint16_t>(tIt.ptr()[2]));
	}

	//Only do quads in case there wasn't triangle data provided
	// otherwise we risk to render triangles double
	if(indices.size() == 0)
	{
		qIt = physx::PxMakeIterator(reinterpret_cast<const T*>(quads.data), quads.stride);
		for (physx::PxU32 i = 0; i < quads.count; ++i, ++qIt)
		{
			indices.push_back(static_cast<uint16_t>(qIt.ptr()[0]));
			indices.push_back(static_cast<uint16_t>(qIt.ptr()[1]));
			indices.push_back(static_cast<uint16_t>(qIt.ptr()[2]));
			indices.push_back(static_cast<uint16_t>(qIt.ptr()[0]));
			indices.push_back(static_cast<uint16_t>(qIt.ptr()[2]));
			indices.push_back(static_cast<uint16_t>(qIt.ptr()[3]));
		}
	}
}

void calc_vertex_normal(std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
{
    for (int i = 0, n = indices.size(); i < n; i += 3)
    {
        auto p0 = vertices[indices[i]].position;
        auto p1 = vertices[indices[i + 1]].position;
        auto p2 = vertices[indices[i + 2]].position;

        auto normal = ((p2 - p0).Cross(p1 - p0)).Normalized();

        vertices[indices[i]].normal += normal;
        vertices[indices[i + 1]].normal += normal;
        vertices[indices[i + 2]].normal += normal;
    }
    for (auto& v : vertices) {
        v.normal.Normalize();
    }
}

}

namespace n3
{

const char* const CompCloth::TYPE_NAME = "n3_cloth";

std::unique_ptr<n0::NodeComp> CompCloth::Clone(const n0::SceneNode& node) const
{
    return nullptr;
}

void CompCloth::BuildFromClothMesh(const ur::Device& dev, const sm::vec3& center, up::cloth::Factory& factory,
                                   up::cloth::ClothMeshData& cloth_mesh)
{
    m_render_mesh = std::make_unique<model::Model::Mesh>();
    BuildRenderMesh(dev, *m_render_mesh, cloth_mesh);

    nv::cloth::Vector<int32_t>::Type phase_type_info;
    m_fabric = factory.CreateFabric(cloth_mesh, sm::vec3(0.0f, -9.8f, 0.0f));

	// Initialize start positions and masses for the actual cloth instance
	// (note: the particle/vertex positions do not have to match the mesh description here. Set the positions to the initial shape of this cloth instance)
	std::vector<sm::vec4> particles_copy;
    auto& vertices = cloth_mesh.Vertices();
	particles_copy.resize(vertices.size());
	for (int i = 0, n = vertices.size(); i < n; i++)
	{
		// To put attachment point closer to each other
        const float mass = cloth_mesh.GetInvMass(i);
        if (mass < 1e-6) {
            vertices[i] = (vertices[i] - center) * 0.85f + center;
        }

        particles_copy[i].x = vertices[i].x;
        particles_copy[i].y = vertices[i].y;
        particles_copy[i].z = vertices[i].z;
        particles_copy[i].w = mass; // w component is 1/mass, or 0.0f for anchored/fixed particles
	}

	// Create the cloth from the initial positions/masses and the fabric
    m_cloth = factory.CreateCloth(*m_fabric, particles_copy);
    // ?
//	particles_copy.clear(); particles_copy.shrink_to_fit();

    m_cloth->SetGravity(sm::vec3(0.0f, -9.8f, 0.0f));

	// Setup phase configs
    auto nv_fabric = std::static_pointer_cast<up::cloth::nv::Fabric>(m_fabric)->GetImpl();
	std::vector<nv::cloth::PhaseConfig> phases(nv_fabric->getNumPhases());
	for (int i = 0; i < (int)phases.size(); i++)
	{
		phases[i].mPhaseIndex = i;
		phases[i].mStiffness = 1.0f;
		phases[i].mStiffnessMultiplier = 1.0f;
		phases[i].mCompressionLimit = 1.0f;
		phases[i].mStretchLimit = 1.0f;
	}
    auto nv_cloth = static_cast<up::cloth::nv::Cloth*>(m_cloth.get())->GetImpl();
	nv_cloth->setPhaseConfig(nv::cloth::Range<nv::cloth::PhaseConfig>(&phases.front(), &phases.back()));
	nv_cloth->setDragCoefficient(0.1f);
	//nv_cloth->setSelfCollisionDistance(0.1f);

    m_solver = factory.CreateSolver();
    m_solver->AddCloth(m_cloth);
}

void CompCloth::UpdateRenderMesh()
{
    auto particles = static_cast<up::cloth::nv::Cloth*>(m_cloth.get())->GetImpl()->getCurrentParticles();
    std::vector<Vertex> vertices(particles.size());
    for (uint32_t i = 0; i < particles.size(); ++i) {
        auto& p = particles[i];
        vertices[i].position.Set(p.x, p.y, -p.z);
        vertices[i].normal.Set(0, 0, 0);
    }
    calc_vertex_normal(vertices, m_indices);

    auto vb = m_render_mesh->geometry.vertex_array->GetVertexBuffer();
    vb->ReadFromMemory(vertices.data(), sizeof(Vertex) * particles.size(), 0);
}

void CompCloth::BuildRenderMesh(const ur::Device& dev, model::Model::Mesh& dst, const up::cloth::ClothMeshData& src)
{
    auto desc = src.GetClothMeshDesc();

    std::vector<Vertex> vertices;
    uint32_t num_vertices = desc->points.count;
    vertices.resize(num_vertices);

    physx::PxStrideIterator<const physx::PxVec3> pIt(
        reinterpret_cast<const physx::PxVec3*>(desc->points.data),
        desc->points.stride
    );
    for (size_t i = 0; i < num_vertices; ++i)
    {
        auto& p = *pIt++;
//        vertices[i].position.Set(p.x, p.y, p.z);
//        vertices[i].position.Set(p.x * 0.01f, p.y * 0.01f, - p.z * 0.01f);
        vertices[i].position.Set(p.x, p.y, -p.z);
        vertices[i].normal.Set(0, 0, 0);
    }

    // build triangle m_indices
    m_indices.clear();
    if (desc->flags & nv::cloth::MeshFlag::e16_BIT_INDICES) {
        gather_indices<physx::PxU16>(m_indices, desc->triangles, desc->quads);
    } else {
        gather_indices<physx::PxU32>(m_indices, desc->triangles, desc->quads);
    }

    calc_vertex_normal(vertices, m_indices);

    auto va = dev.CreateVertexArray();

    auto usage = ur::BufferUsageHint::StaticDraw;

    auto ibuf_sz = sizeof(unsigned short) * m_indices.size();
    auto ibuf = dev.CreateIndexBuffer(usage, ibuf_sz);
    ibuf->ReadFromMemory(m_indices.data(), ibuf_sz, 0);
    va->SetIndexBuffer(ibuf);

    auto vbuf_sz = sizeof(float) * vertices.size();
    auto vbuf = dev.CreateVertexBuffer(ur::BufferUsageHint::StaticDraw, vbuf_sz);
    vbuf->ReadFromMemory(vertices.data(), vbuf_sz, 0);
    va->SetVertexBuffer(vbuf);

    std::vector<std::shared_ptr<ur::VertexBufferAttribute>> vbuf_attrs(2);
    // position
    vbuf_attrs[0] = std::make_shared<ur::VertexBufferAttribute>(
        0, ur::ComponentDataType::Float, 3, 0, 24
    );
    // normal
    vbuf_attrs[1] = std::make_shared<ur::VertexBufferAttribute>(
        1, ur::ComponentDataType::Float, 3, 12, 24
    );
    va->SetVertexBufferAttrs(vbuf_attrs);

    dst.geometry.vertex_array = va;
    dst.geometry.sub_geometries.push_back(model::SubmeshGeometry(true, m_indices.size(), 0));
    dst.geometry.sub_geometry_materials.push_back(0);
}

}