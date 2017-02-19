#include <cassert>

#include <INETDefs.h>
#include <Ieee802Ctrl.h>

#include "MobileRangingApplication.h"
#include "RangingHost.h"
#include "Utilities.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(MobileRangingApplication);

void
MobileRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& broadcastReplyDelayParamater = par ("broadcastReplyDelay");
        assert (broadcastReplyDelayParamater.getType () == cPar::LONG);
        broadcastReplyDelay = SimTime {broadcastReplyDelayParamater.longValue (), SIMTIME_US};
    }
}

void
MobileRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())    {
        // TODO
    }
    else    {
        handleRangingPacket (check_and_cast<RangingPacket*> (message));
    }

    delete message;
}

void
MobileRangingApplication::handleRangingPacket (RangingPacket* packet)
{
    // Prepare & send reply
    auto packetControlInformation = check_and_cast<Ieee802Ctrl*> (packet->getControlInfo ());
    unique_ptr<RangingPacket> reply {new RangingPacket};

    reply->setBitLength (4);
    reply->setSequenceNumber (packet->getSequenceNumber () + 1);

    // Compute delay
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    SimTime delay {broadcastReplyDelay - (simTime () - rangingHost->getRxBeginTimestamp ())};
    EXPECT (delay > 0, "Cannot send MAC packet with negative delay");

    sendMacPacket (packetControlInformation->getSourceAddress (), move (reply), delay);
}

}; // namespace ipin2017
