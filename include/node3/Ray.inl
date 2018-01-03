#pragma once

namespace n3
{

// inline 
// Ray::Ray()
// 	: m_start(0, 0, 0)
// 	, m_dir(0, 0, 1, 1)
// {
// }

inline 
Ray::Ray(const sm::vec3& start, const sm::vec3& dir)
	: m_start(start)
	, m_dir_vec(dir)
{
}

inline 
void Ray::Translate(const sm::vec3& offset)
{
	m_start += offset;
}

// inline 
// void Ray::Rotate(const sm::mat4& mat)
// {
// 	m_dir = mat * m_dir;
// }

inline 
const sm::vec3& Ray::Start() const 
{
	return m_start;
}

}