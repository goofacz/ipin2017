#pragma once

#include <omnetpp.h>

#include "RangingApplication.h"
#include "RangingPacket_m.h"

namespace ipin2017
{

class MobileRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleRangingPacket (RangingPacket* packet);

    omnetpp::SimTime broadcastReplyDelay {0};
};

}; // namespace ipin2017
