#pragma once

#include <fstream>
#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class TDoAAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void finish() override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handlFrame (BeaconFrame* frame);

    void handleSelfMessage ();

    unsigned int getCurrentPacketSequenceNumber () const;

    unsigned int getNextPacketSequenceNumber ();

    void sendBeaconFrame ();

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    omnetpp::SimTime broadcastBeaconDelay {0};
    inet::MACAddress echoAnchorAddress;
    omnetpp::SimTime echoBeaconDelay {0};
    unsigned int packetSequenceNumberGenerator {0};
    omnetpp::SimTime beaconReceptionTimestamp {0};
};

}; // namespace ipin2017
