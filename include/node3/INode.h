#pragma once

#include "node3/IModel.h"

#include <SM_Vector.h>
#include <SM_Matrix.h>

namespace n3
{

class INode : private cu::Uncopyable
{
public:
	INode(const ModelPtr& model);

	virtual bool Update() = 0;

	const ModelPtr& GetModel() const { return m_model; }

//	const sm::mat4& GetMat() const { return m_mat; }

	const sm::vec3& 
		GetPos() const { return m_srt.position; }
	const sm::Quaternion& 
		GetAngle() const { return m_srt.angle; }
	const sm::vec3& 
		GetScale() const { return m_srt.scale; }

	void SetPos(const sm::vec3& pos);
	void SetAngle(const sm::Quaternion& angle);
	void SetScale(const sm::vec3& scale);

	void Translate(const sm::vec3& offset);
	void Rotate(const sm::Quaternion& delta);
	
private:
	struct SRT
	{
		sm::vec3       position;
		sm::Quaternion angle;
		sm::vec3       scale;

		SRT() : scale(1, 1, 1) {}
	};

protected:
	ModelPtr m_model = nullptr;

	SRT      m_srt;
//	sm::mat4 m_mat;

}; // INode

typedef std::shared_ptr<INode>       NodePtr;
typedef std::shared_ptr<const INode> NodeConstPtr;

}