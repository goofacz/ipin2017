#pragma once

#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "MasterAnchorSelfMessage_m.h"
#include "RangingReplyFrame_m.h"
#include "BackhaulMessage.h"
#include "Ranging.h"

namespace ipin2017
{

class MasterAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleSelfMessage (MasterAnchorSelfMessage* message);

    void handleFrame (RangingReplyFrame* frame);

    void handleMessage (BackhaulMessage* message);

    void handleBroadcastBeaconEvent ();

    int getBroadcastBeaconDelay () const;

    unsigned int getCurrentPacketSequenceNumber () const;

    unsigned int getNextPacketSequenceNumber ();

    void onTxStateChangedCallback (inet::physicallayer::IRadio::TransmissionState state);

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    omnetpp::SimTime frameTransmissionTimestamp {0};
    omnetpp::SimTime frameReceptionTimestamp {0};
    int broadcastBeaconDelay = 0;
    unsigned int packetSequenceNumberGenerator = 0;

    std::vector<Beacon> beacons;
};

}; // namespace ipin2017
