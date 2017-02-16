#pragma once

#include <omnetpp.h>

#include "RangingApplication.h"
#include "MasterAnchorSelfMessage_m.h"
#include "RangingPacket_m.h"

namespace ipin2017
{

class MasterAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleSelfMessage (MasterAnchorSelfMessage* message);

    void handleRangingPacket (RangingPacket* packet);

    void handleBroadcastBeaconEvent ();

    int getBroadcastBeaconDelay () const;

    unsigned int getCurrentPacketSequenceNumber () const;

    unsigned int getNextPacketSequenceNumber ();

    int broadcastBeaconDelay = 0;
    unsigned int packetSequenceNumberGenerator = 0;

};

}; // namespace ipin2017
