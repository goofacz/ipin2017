#include <cassert>

#include <INETDefs.h>
#include <Ieee802Ctrl.h>
#include <IdealMacFrame_m.h>

#include "MobileRangingApplication.h"
#include "RangingHost.h"
#include "Utilities.h"
#include "RangingReplyFrame_m.h"

using namespace inet;
using namespace inet::physicallayer;
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

        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        rangingHost->addRxStateChangedCallback ([this] (IRadio::ReceptionState state) { this->onRxStateChangedCallback (state); });
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
        const auto frame = check_and_cast<const Frame*> (message);
        switch (frame->getType ())
        {
            case BEACON_FRAME:
                handleFrame (check_and_cast<BeaconFrame*> (message));
                break;
            default:
                throw cRuntimeError ("Unsupported frame");
        }
    }

    delete message;
}

void
MobileRangingApplication::handleFrame (BeaconFrame* beaconFrame)
{
    // Prepare & send reply
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    auto packetControlInformation = check_and_cast<Ieee802Ctrl*> (beaconFrame->getControlInfo ());
    unique_ptr<RangingReplyFrame> rangingReplyFrame {new RangingReplyFrame};

    rangingReplyFrame->setBitLength (10);
    rangingReplyFrame->setSequenceNumber (beaconFrame->getSequenceNumber () + 1);
    rangingReplyFrame->setRealPosition (rangingHost->getCurrentPosition ());

    // Compute delay
    SimTime delay {broadcastReplyDelay - (simTime () - broadcastReceptionTimestamp)};
    EXPECT (delay > 0, "Cannot send MAC packet with negative delay");

    sendFrame (packetControlInformation->getSourceAddress (), unique_ptr<Frame> (rangingReplyFrame.release ()), delay);
}

void
MobileRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)    {
        broadcastReceptionTimestamp = simTime ();
    }
}

}; // namespace ipin2017
