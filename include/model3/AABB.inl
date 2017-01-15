#ifndef _MODEL3_AABB_INL_
#define _MODEL3_AABB_INL_

namespace m3
{

inline AABB::AABB() 
{ 
	MakeEmpty(); 
}

inline void AABB::MakeEmpty() 
{
	for (int i = 0; i < 3; ++i) {
		m_min.xyz[i] = FLT_MAX;
		m_max.xyz[i] = -FLT_MAX;
	}
}

inline void AABB::Combine(const sm::vec3& pos) 
{
	for (int i = 0; i < 3; ++i) {
		if (pos.xyz[i] < m_min.xyz[i]) {
			m_min.xyz[i] = pos.xyz[i];
		}
		if (pos.xyz[i] > m_max.xyz[i]) {
			m_max.xyz[i] = pos.xyz[i];
		}
	}
}

inline void AABB::Translate(const sm::vec3& offset)
{
	m_min += offset;
	m_max += offset;
}

inline void AABB::Rotate(const sm::mat4& mat)
{
	m_min = mat * m_min;
	m_max = mat * m_max;
}

inline const sm::vec3 AABB::Max() const 
{ 
	return m_max; 
}

inline const sm::vec3 AABB::Min() const 
{ 
	return m_min; 
}

}

#endif // _MODEL3_AABB_INL_
