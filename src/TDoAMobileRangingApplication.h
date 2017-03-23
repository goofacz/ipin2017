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
    struct ReceivedBeacon
    {
        ReceivedBeacon (std::unique_ptr<const BeaconFrame> beacon,
                        omnetpp::SimTime receptionTimestamp,
                        inet::Coord realPosition);

        std::unique_ptr<const BeaconFrame> beacon;
        omnetpp::SimTime receptionTimestamp;
        inet::Coord realPosition;
    };

  private:
    void initialize (int stage) override;

    void finish() override;

    void handleMessage (omnetpp::cMessage* message) override;

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    omnetpp::SimTime beaconReceptionTimestamp {0};
    std::vector<ReceivedBeacon> receivedBeacons;
};

}; // namespace ipin2017
