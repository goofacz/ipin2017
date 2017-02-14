#pragma once

#include <memory>

#include <omnetpp.h>
#include <MACAddress.h>

namespace ipin2017
{

class RangingApplication :
    public omnetpp::cSimpleModule
{
    protected:
        void initialize (int stage) override;

        const inet::MACAddress& getLocalAddress () const;

        void sendMacPacket (const inet::MACAddress& destinationAddress,
                            std::unique_ptr<omnetpp::cPacket> packet);

    private:
        int numInitStages() const override;

        inet::MACAddress localAddress;
};

} // namespace ipin2017
