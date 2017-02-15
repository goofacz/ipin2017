#pragma once

#include <omnetpp.h>

#include "RangingApplication.h"
#include "AnchorSelfMessage_m.h"

namespace ipin2017
{

class AnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleSelfMessage (AnchorSelfMessage* message);

    void handleBroadcastBeaconEvent ();

    int getBroadcastBeaconDelay () const;

    int broadcastBeaconDelay;
};

}; // namespace ipin2017
