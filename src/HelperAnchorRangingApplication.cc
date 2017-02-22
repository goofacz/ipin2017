#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <HelperAnchorRangingApplication.h>
#include <MACAddress.h>

#include "RangingHost.h"
#include "BackhaulMessage.h"
#include "Ieee802Ctrl.h"

using namespace inet;
using namespace inet::physicallayer;
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
        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        rangingHost->addRxStateChangedCallback ([this] (IRadio::ReceptionState state) { this->onRxStateChangedCallback (state); });
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
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    unique_ptr<BackhaulMessage> message {new BackhaulMessage};
    message->setAddress (rangingHost->getLocalAddress ());
    message->setPosition (rangingHost->getCurrentPosition ());
    message->setFrame (frame->dup ());
    message->setReceptionTimestamp (frameReceptionTimestamp);

    for (int i {0}; i < gateSize ("backhaulOut"); i++) {
        send (message->dup (), "backhaulOut", i);
    }
}

void
HelperAnchorRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)    {
        frameReceptionTimestamp = simTime ();
    }
}

}; // namespace ipin2017
