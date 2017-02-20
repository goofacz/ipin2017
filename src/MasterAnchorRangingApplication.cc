#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <MasterAnchorRangingApplication.h>
#include <MACAddress.h>

#include "BeaconFrame_m.h"

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
        const auto arrivalGate = message->getArrivalGate ();

        if (strcmp (arrivalGate->getBaseName (), "in") == 0)
        {
            const auto frame = check_and_cast<const Frame*> (message);
            switch (frame->getType ())
            {
                case RANGING_REPLY_FRAME:
                    handleFrame (check_and_cast<RangingReplyFrame*> (message));
                    break;
                default:
                    throw cRuntimeError ("Unsupported frame");
            }
        }
        else if (strcmp (arrivalGate->getBaseName (), "backhaulIn") == 0)
        {
            // TODO
        }
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
MasterAnchorRangingApplication::handleFrame (RangingReplyFrame* frame)
{
    if (frame->getSequenceNumber () != getCurrentPacketSequenceNumber () + 1)
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
    unique_ptr<BeaconFrame> frame {new BeaconFrame {}};

    frame->setBitLength (10);
    frame->setSequenceNumber (getNextPacketSequenceNumber ());

    sendFrame (MACAddress::BROADCAST_ADDRESS, unique_ptr<Frame> (frame.release ()));

    // Schedule next beacon
    unique_ptr<MasterAnchorSelfMessage> message {new MasterAnchorSelfMessage {}};
    message->setEventType (BROADCAST_BEACON);

    scheduleSelfMessage (move (message), getBroadcastBeaconDelay (), SIMTIME_MS);
}

}; // namespace ipin2017
