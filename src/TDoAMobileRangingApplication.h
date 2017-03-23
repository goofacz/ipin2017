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
    using BeaconPair = std::pair<std::unique_ptr<const BeaconFrame>, omnetpp::SimTime>;

  private:
    void initialize (int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    omnetpp::SimTime beaconReceptionTimestamp {0};
    std::vector<BeaconPair> beaconPairs;
};

}; // namespace ipin2017
