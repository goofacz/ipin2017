#pragma once

#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class WhistleMobileRangingApplication :
    public RangingApplication
{
  private:
    void initialize (int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    unsigned int getNextPacketSequenceNumber ();

    omnetpp::SimTime frameTransmissionInterval {0};
    unsigned int packetSequenceNumberGenerator {0};
};

}; // namespace ipin2017
