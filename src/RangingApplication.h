#pragma once

#include <memory>

#include <omnetpp.h>
#include <MACAddress.h>

#include "Frame_m.h"

namespace ipin2017
{

class RangingApplication :
    public omnetpp::cSimpleModule
{
    protected:
        void initialize (int stage) override;

        void sendFrame (const inet::MACAddress& destinationAddress,
                        std::unique_ptr<Frame> frame,
                        const omnetpp::SimTime& delay = omnetpp::SimTime {0, omnetpp::SIMTIME_MS});

        void scheduleSelfMessage (std::unique_ptr<omnetpp::cMessage> message,
                                  unsigned int delay,
                                  omnetpp::SimTimeUnit delay_unit);

    private:
        int numInitStages () const override;
};

} // namespace ipin2017
