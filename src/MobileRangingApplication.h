#pragma once

#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class MobileRangingApplication :
    public RangingApplication
{
  private:
    void initialize (int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleFrame (BeaconFrame* beaconFrame);

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    omnetpp::SimTime broadcastReplyDelay {0};
    omnetpp::SimTime broadcastReceptionTimestamp {0};
};

}; // namespace ipin2017
