#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <MACAddress.h>

#include "AnchorRangingApplication.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(AnchorRangingApplication);

void
AnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& broadcastBeaconParamater = par ("broadcastBeacon");
        assert (broadcastBeaconParamater.getType () == cPar::BOOL);
        const auto broadcastBeacon = broadcastBeaconParamater.boolValue ();

        const auto& broadcastBeaconDelayParamater = par ("broadcastBeaconDelay");
        assert (broadcastBeaconDelayParamater.getType () == cPar::LONG);
        broadcastBeaconDelay = broadcastBeaconDelayParamater.longValue ();

        if (broadcastBeacon)
        {
            unique_ptr<AnchorSelfMessage> message {new AnchorSelfMessage {}};
            message->setEventType (BROADCAST_BEACON);
            scheduleSelfMessage (move (message), broadcastBeaconDelay, SIMTIME_MS);
        }
    }
}

void
AnchorRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())
    {
        handleSelfMessage (check_and_cast<AnchorSelfMessage*> (message));
    }
    else
    {
        handleRangingPacket (check_and_cast<RangingPacket*> (message));
    }
}

void
AnchorRangingApplication::handleSelfMessage (AnchorSelfMessage* message)
{
    switch (message->getEventType ())
    {
        case BROADCAST_BEACON:
            handleBroadcastBeaconEvent ();
            break;
    }
}

void
AnchorRangingApplication::handleRangingPacket (RangingPacket* packet)
{
    if (packet->getSequenceNumber () != getCurrentPacketSequenceNumber () + 1)
    {
        // TODO
    }

    // TODO
}

int
AnchorRangingApplication::getBroadcastBeaconDelay () const
{
    return broadcastBeaconDelay;
}

unsigned int
AnchorRangingApplication::getCurrentPacketSequenceNumber () const
{
    return packetSequenceNumberGenerator;
}

unsigned int
AnchorRangingApplication::getNextPacketSequenceNumber ()
{
    return ++packetSequenceNumberGenerator;
}

void
AnchorRangingApplication::handleBroadcastBeaconEvent ()
{
    // Prepare & send beacon
    unique_ptr<RangingPacket> packet {new RangingPacket {}};

    packet->setBitLength (10);
    packet->setSequenceNumber (getNextPacketSequenceNumber ());

    sendMacPacket (MACAddress::BROADCAST_ADDRESS, move (packet));

    // Schedule next beacon
    unique_ptr<AnchorSelfMessage> message {new AnchorSelfMessage {}};
    message->setEventType (BROADCAST_BEACON);

    scheduleSelfMessage (move (message), getBroadcastBeaconDelay (), SIMTIME_MS);
}

}; // namespace ipin2017
