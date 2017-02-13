#pragma once

#include <omnetpp.h>
#include <MACAddress.h>

namespace ipin2017 {


class RangingApplication :
    public omnetpp::cSimpleModule
{
    protected:
        void initialize (int stage) override;

        const inet::MACAddress& getLocalAddress () const;

    private:
        int numInitStages() const override;

        inet::MACAddress localAddress;
};

} //namespace ipin2017
