#pragma once

#include <node0/NodeComp.h>

#include <memory>

namespace up { namespace rigid { class Body; } }

namespace n3
{

class CompRigid : public n0::NodeComp
{
public:
    virtual ~CompRigid();

    virtual const char* Type() const override { return TYPE_NAME; }
    virtual n0::CompID TypeID() const override {
        return n0::GetCompTypeID<CompRigid>();
    }
    virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

    auto& GetBody() const { return m_body; }
    void SetBody(const std::shared_ptr<up::rigid::Body>& body) {
        m_body = body;
    }

    static const char* const TYPE_NAME;

private:
    std::shared_ptr<up::rigid::Body> m_body = nullptr;

};  // CompRigid

}