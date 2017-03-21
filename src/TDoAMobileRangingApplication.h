#pragma once

#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class TDoAMobileRangingApplication :
    public RangingApplication
{
  private:
    void initialize (int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleFrame (BeaconFrame* beaconFrame);

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);
};

}; // namespace ipin2017
