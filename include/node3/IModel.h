#pragma once

#include <memory>

#include <cu/uncopyable.h>

namespace n3
{

class RenderParams;

class IModel : private cu::Uncopyable
{
public:
	virtual ~IModel() {}
	virtual size_t Type() const = 0;
	virtual void Draw(const RenderParams&) const = 0;

}; // IModel

typedef std::shared_ptr<IModel>       ModelPtr;
typedef std::shared_ptr<const IModel> ModelConstPtr;

}