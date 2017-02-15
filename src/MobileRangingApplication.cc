#include <INETDefs.h>
#include <Ieee802Ctrl.h>

#include "MobileRangingApplication.h"
#include "RangingPacket_m.h"

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
        // TODO
    }
}

void
MobileRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())
    {
        // TODO
    }
    else
    {
        auto packet = check_and_cast<RangingPacket*> (message);
        auto packetControlInformation = check_and_cast<Ieee802Ctrl*> (packet->getControlInfo ());
        unique_ptr<RangingPacket> reply {new RangingPacket};
        reply->setBitLength (4);
        sendMacPacket (packetControlInformation->getSourceAddress (), move (reply));
    }
}

}; // namespace ipin2017
