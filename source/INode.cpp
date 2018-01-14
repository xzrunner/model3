#include "node3/INode.h"

namespace n3
{

INode::INode(const ModelPtr& model) 
	: m_model(model) 
{
}

void INode::SetPos(const sm::vec3& pos)
{
	m_srt.position = pos;
}

void INode::SetAngle(const sm::Quaternion& angle)
{
	m_srt.angle = angle;
}

void INode::SetScale(const sm::vec3& scale)
{
	m_srt.scale = scale;
}

void INode::Translate(const sm::vec3& offset)
{
	m_srt.position += offset;
}

void INode::Rotate(const sm::Quaternion& delta)
{
	m_srt.angle = delta.Rotated(m_srt.angle);
}

}