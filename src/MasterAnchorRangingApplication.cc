#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <MasterAnchorRangingApplication.h>
#include <MACAddress.h>


using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(MasterAnchorRangingApplication);

void
MasterAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& broadcastBeaconDelayParamater = par ("broadcastBeaconDelay");
        assert (broadcastBeaconDelayParamater.getType () == cPar::LONG);
        broadcastBeaconDelay = broadcastBeaconDelayParamater.longValue ();

        unique_ptr<MasterAnchorSelfMessage> message {new MasterAnchorSelfMessage {}};
        message->setEventType (BROADCAST_BEACON);
        scheduleSelfMessage (move (message), broadcastBeaconDelay, SIMTIME_MS);
    }
}

void
MasterAnchorRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())
    {
        handleSelfMessage (check_and_cast<MasterAnchorSelfMessage*> (message));
    }
    else
    {
        handleRangingPacket (check_and_cast<RangingPacket*> (message));
    }

    delete message;
}

void
MasterAnchorRangingApplication::handleSelfMessage (MasterAnchorSelfMessage* message)
{
    switch (message->getEventType ())
    {
        case BROADCAST_BEACON:
            handleBroadcastBeaconEvent ();
            break;
    }
}

void
MasterAnchorRangingApplication::handleRangingPacket (RangingPacket* packet)
{
    if (packet->getSequenceNumber () != getCurrentPacketSequenceNumber () + 1)
    {
        // TODO
    }

    // TODO
}

int
MasterAnchorRangingApplication::getBroadcastBeaconDelay () const
{
    return broadcastBeaconDelay;
}

unsigned int
MasterAnchorRangingApplication::getCurrentPacketSequenceNumber () const
{
    return packetSequenceNumberGenerator;
}

unsigned int
MasterAnchorRangingApplication::getNextPacketSequenceNumber ()
{
    return ++packetSequenceNumberGenerator;
}

void
MasterAnchorRangingApplication::handleBroadcastBeaconEvent ()
{
    // Prepare & send beacon
    unique_ptr<RangingPacket> packet {new RangingPacket {}};

    packet->setBitLength (10);
    packet->setSequenceNumber (getNextPacketSequenceNumber ());

    sendMacPacket (MACAddress::BROADCAST_ADDRESS, move (packet));

    // Schedule next beacon
    unique_ptr<MasterAnchorSelfMessage> message {new MasterAnchorSelfMessage {}};
    message->setEventType (BROADCAST_BEACON);

    scheduleSelfMessage (move (message), getBroadcastBeaconDelay (), SIMTIME_MS);
}

}; // namespace ipin2017
