#pragma once

#include "node3/NodeComponent.h"

#include <SM_Vector.h>
#include <SM_Quaternion.h>
#include <SM_Matrix.h>

namespace n3
{

class CompTransform : public NodeComponent
{
public:
	CompTransform();

	virtual const char* Type() const override { return TYPE_NAME; }

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(const rapidjson::Value& val) override;

	const sm::vec3& GetPosition() const { return m_position; }
	const sm::Quaternion& GetAngle() const { return m_angle; }
	const sm::vec3& GetScale() const { return m_scale; }

	sm::mat4 GetTransformMat() const;

	void SetPosition(const sm::vec3& pos) { m_position = pos; }
	void SetAngle(const sm::Quaternion& angle) { m_angle = angle; }
	void SetScale(const sm::vec3& scale) { m_scale = scale; }

	void Translate(const sm::vec3& offset) { m_position += offset; }
	void Rotate(const sm::Quaternion& delta) { m_angle = delta.Rotated(m_angle); }

	static const char* const TYPE_NAME;

private:
	sm::vec3       m_position;
	sm::Quaternion m_angle;
	sm::vec3       m_scale;

}; // CompTransform

}