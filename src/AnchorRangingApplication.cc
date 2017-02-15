#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <MACAddress.h>

#include "AnchorRangingApplication.h"
#include "RangingPacket_m.h"

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
}

void
AnchorRangingApplication::handleSelfMessage (AnchorSelfMessage* message)
{
    assert (message->isSelfMessage ());
    switch (message->getEventType ())
    {
        case BROADCAST_BEACON:
            handleBroadcastBeaconEvent ();
            break;
    }
}

int
AnchorRangingApplication::getBroadcastBeaconDelay () const
{
    return broadcastBeaconDelay;
}

void
AnchorRangingApplication::handleBroadcastBeaconEvent ()
{
    unique_ptr<RangingPacket> packet {new RangingPacket {}};
    packet->setBitLength (10);
    sendMacPacket (MACAddress::BROADCAST_ADDRESS, move (packet));

    unique_ptr<AnchorSelfMessage> message {new AnchorSelfMessage {}};
    message->setEventType (BROADCAST_BEACON);
    scheduleSelfMessage (move (message), getBroadcastBeaconDelay (), SIMTIME_MS);
}

}; // namespace ipin2017
