#pragma once

#include <fstream>
#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "MasterAnchorSelfMessage_m.h"
#include "RangingReplyFrame_m.h"
#include "BeaconFrame_m.h"
#include "BackhaulMessage.h"
#include "Ranging.h"

namespace ipin2017
{

class MasterAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void finish() override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleSelfMessage (MasterAnchorSelfMessage* message);

    void handleFrame (RangingReplyFrame* frame);

    void handleBackhaulMessage (const BackhaulMessage* message);

    void handleBackhaulMessage (const BackhaulMessage* message,
                                const RangingReplyFrame* frame);

    void handleBackhaulMessage (const BackhaulMessage* message,
                                const BeaconFrame* frame);

    void handleBroadcastBeaconEvent ();

    int getBroadcastBeaconDelay () const;

    unsigned int getCurrentPacketSequenceNumber () const;

    unsigned int getNextPacketSequenceNumber ();

    void onTxStateChangedCallback (inet::physicallayer::IRadio::TransmissionState state);

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    void storeSimulationResults () noexcept;

    omnetpp::SimTime frameReceptionTimestamp {0};
    int broadcastBeaconDelay {0};
    unsigned int packetSequenceNumberGenerator {0};
    std::string simulationResultSuffix {""};

    std::vector<Beacon> beacons;
};

}; // namespace ipin2017
