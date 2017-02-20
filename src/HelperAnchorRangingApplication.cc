#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <HelperAnchorRangingApplication.h>
#include <MACAddress.h>

#include "RangingHost.h"
#include "BackhaulMessage_m.h"
#include "Ieee802Ctrl.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(HelperAnchorRangingApplication);

void
HelperAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void
HelperAnchorRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())
    {
        // TODO
    }
    else
    {
        auto frame = check_and_cast<Frame*> (message);
        handleFrame (frame);
    }

    delete message;
}

void
HelperAnchorRangingApplication::handleFrame (Frame* frame)
{
    const auto frameControlInformation = check_and_cast<Ieee802Ctrl*> (frame->getControlInfo ());
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    unique_ptr<BackhaulMessage> message {new BackhaulMessage};

    message->setReceptionTimestamp (rangingHost->getRxBeginTimestamp ());
    message->setSourceAddress (frameControlInformation->getSourceAddress ());
    message->setSequenceNumber (frame->getSequenceNumber ());

    for (int i {0}; i < gateSize ("backhaulOut"); i++) {
        send (message.release (), "backhaulOut", i);
    }
}

}; // namespace ipin2017
