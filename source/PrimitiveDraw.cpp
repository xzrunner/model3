#include "model3/PrimitiveDraw.h"
#include "model3/AABB.h"

#include <rvg.h>
#include <shaderlab/ShaderMgr.h>
#include <shaderlab/Shape3Shader.h>

namespace m3
{

void PrimitiveDraw::Init()
{
	rvg_style_init();
}

void PrimitiveDraw::SetColor(uint32_t abgr)
{
	sl::ShaderMgr* mgr = sl::ShaderMgr::Instance();
	auto shader = static_cast<sl::Shape3Shader*>(mgr->GetShader(sl::SHAPE3));
	shader->SetColor(abgr);
}

void PrimitiveDraw::Line(const sm::vec3& p0, const sm::vec3& p1)
{
	SetShader(sl::SHAPE3);
	rvg_line3(p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);
}

void PrimitiveDraw::TriLine(const sm::vec3& p0, const sm::vec3& p1, const sm::vec3& p2)
{
	sm::vec3 vertices[] = {p0, p1, p1, p2, p2, p0};
	SetShader(sl::SHAPE3);
	rvg_lines3(&vertices[0].x, 6);
}

void PrimitiveDraw::Cube(const AABB& aabb)
{
	PrimitiveDraw::Cube(aabb.Min(), aabb.Max());
}

void PrimitiveDraw::Cube(const sm::mat4& mat, const AABB& aabb)
{
	//const sm::vec3& min = aabb.Min();
	//const sm::vec3& max = aabb.Max();

	//sm::vec3 vertices[8];
	//vertices[0] = mat * min; 
	//vertices[1] = mat * sm::vec3(max.x, min.y, min.z);
	//vertices[2] = mat * sm::vec3(max.x, max.y, min.z);
	//vertices[3] = mat * sm::vec3(min.x, max.y, min.z);
	//vertices[4] = mat * sm::vec3(min.x, min.y, max.z);
	//vertices[5] = mat * sm::vec3(max.x, min.y, max.z);
	//vertices[6] = mat * max;
	//vertices[7] = mat * sm::vec3(min.x, max.y, max.z);

	//unsigned short indices[24];
	//int idx = 0;
	//indices[idx++] = 0;
	//indices[idx++] = 1;
	//indices[idx++] = 1;
	//indices[idx++] = 2;
	//indices[idx++] = 2;
	//indices[idx++] = 3;
	//indices[idx++] = 3;
	//indices[idx++] = 0;

	//indices[idx++] = 4;
	//indices[idx++] = 5;
	//indices[idx++] = 5;
	//indices[idx++] = 6;
	//indices[idx++] = 6;
	//indices[idx++] = 7;
	//indices[idx++] = 7;
	//indices[idx++] = 4;

	//indices[idx++] = 0;
	//indices[idx++] = 4;
	//indices[idx++] = 1;
	//indices[idx++] = 5;
	//indices[idx++] = 2;
	//indices[idx++] = 6;
	//indices[idx++] = 3;
	//indices[idx++] = 7;

	//ShaderMgr* mgr = ShaderMgr::Instance();
	//mgr->Shape();
	//mgr->DrawShape(GL_LINES, &vertices[0].x, 8, color, indices, 24);
}

void PrimitiveDraw::Cube(const sm::vec3& min, const sm::vec3& max)
{
	//float vertices[24];
	//int idx = 0;
	//
	//vertices[idx++] = min.x;
	//vertices[idx++] = min.y;
	//vertices[idx++] = min.z;

	//vertices[idx++] = max.x;
	//vertices[idx++] = min.y;
	//vertices[idx++] = min.z;

	//vertices[idx++] = max.x;
	//vertices[idx++] = max.y;
	//vertices[idx++] = min.z;

	//vertices[idx++] = min.x;
	//vertices[idx++] = max.y;
	//vertices[idx++] = min.z;

	//vertices[idx++] = min.x;
	//vertices[idx++] = min.y;
	//vertices[idx++] = max.z;

	//vertices[idx++] = max.x;
	//vertices[idx++] = min.y;
	//vertices[idx++] = max.z;

	//vertices[idx++] = max.x;
	//vertices[idx++] = max.y;
	//vertices[idx++] = max.z;

	//vertices[idx++] = min.x;
	//vertices[idx++] = max.y;
	//vertices[idx++] = max.z;

	//unsigned short indices[24];
	//idx = 0;
	//indices[idx++] = 0;
	//indices[idx++] = 1;
	//indices[idx++] = 1;
	//indices[idx++] = 2;
	//indices[idx++] = 2;
	//indices[idx++] = 3;
	//indices[idx++] = 3;
	//indices[idx++] = 0;

	//indices[idx++] = 4;
	//indices[idx++] = 5;
	//indices[idx++] = 5;
	//indices[idx++] = 6;
	//indices[idx++] = 6;
	//indices[idx++] = 7;
	//indices[idx++] = 7;
	//indices[idx++] = 4;

	//indices[idx++] = 0;
	//indices[idx++] = 4;
	//indices[idx++] = 1;
	//indices[idx++] = 5;
	//indices[idx++] = 2;
	//indices[idx++] = 6;
	//indices[idx++] = 3;
	//indices[idx++] = 7;

	//ShaderMgr* mgr = ShaderMgr::Instance();
	//mgr->Shape();
	//mgr->DrawShape(GL_LINES, vertices, 8, color, indices, 24);
}

void PrimitiveDraw::Cube(const sm::vec3& min, const sm::vec3& max, int texid)
{
	//float vertices[2 * 6 * 3 * 3];
	//int idx_vert = 0;

	//float texcoords[2 * 6 * 3 * 2];
	//int idx_tex = 0;

	//// front
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 1;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//// back
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 1;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//// left
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 1;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//// right
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 1;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//// bottom
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 1;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = min.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//// top
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 1;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;

	//vertices[idx_vert++] = min.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 0; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = min.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 0;
	//vertices[idx_vert++] = max.x; vertices[idx_vert++] = max.y; vertices[idx_vert++] = max.z;
	//texcoords[idx_tex++] = 1; texcoords[idx_tex++] = 1;	

	//e3d::ShaderMgr* mgr = e3d::ShaderMgr::Instance();
	//mgr->Sprite();

	//mgr->DrawTri(vertices, texcoords, 2 * 6 * 3, texid);
}

void PrimitiveDraw::Cross(const sm::vec3& center, const sm::vec3& size)
{
	float vertices[18];
	int idx = 0;

	vertices[idx++] = center.x - size.x;
	vertices[idx++] = center.y;
	vertices[idx++] = center.z;
	vertices[idx++] = center.x + size.x;
	vertices[idx++] = center.y;
	vertices[idx++] = center.z;

	vertices[idx++] = center.x;
	vertices[idx++] = center.y - size.y;
	vertices[idx++] = center.z;
	vertices[idx++] = center.x;
	vertices[idx++] = center.y + size.y;
	vertices[idx++] = center.z;

	vertices[idx++] = center.x;
	vertices[idx++] = center.y;
	vertices[idx++] = center.z - size.x;
	vertices[idx++] = center.x;
	vertices[idx++] = center.y;
	vertices[idx++] = center.z + size.z;

	SetShader(sl::SHAPE3);
	rvg_lines3(vertices, 6);
}

void PrimitiveDraw::Grids(const sm::vec3& min, const sm::vec3& max, const sm::vec3& size)
{
	std::vector<sm::vec3> lines;
	int cx = size.x ? ceil(max.x - min.x) / size.x : 1;
	int cy = size.y ? ceil(max.y - min.y) / size.y : 1;
	int cz = size.z ? ceil(max.z - min.z) / size.z : 1;
	lines.reserve(cx * cy * cz * 2);

	for (float z = min.z; z <= max.z; z += size.z) {
		for (float x = min.y; x <= max.x; x += size.x) {
			lines.push_back(sm::vec3(x, min.y, z));
			lines.push_back(sm::vec3(x, max.y, z));
			if (size.x == 0) {
				break;
			}
		}
		for (float y = min.y; y <= max.y; y += size.y) {
			lines.push_back(sm::vec3(min.x, y, z));
			lines.push_back(sm::vec3(max.x, y, z));
			if (size.x == 0) {
				break;
			}
		}
		if (size.x == 0) {
			break;
		}
	}

	SetShader(sl::SHAPE3);
	rvg_lines3(&lines[0].x, lines.size());
}

void PrimitiveDraw::Points(const std::vector<sm::vec3>& points)
{
	SetShader(sl::SHAPE3);
	for (auto& p : points) {
		rvg_point3(p.x, p.y, p.z);
	}
}

void PrimitiveDraw::SetShader(int shader_type)
{
	sl::ShaderMgr::Instance()->SetShader(static_cast<sl::ShaderType>(shader_type));
}

}