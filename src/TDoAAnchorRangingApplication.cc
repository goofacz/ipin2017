#include <cassert>
#include <memory>
#include <algorithm>
#include <fstream>

#include <INETDefs.h>
#include <MACAddress.h>
#include <IdealMacFrame_m.h>
#include <Ieee802Ctrl.h>

#include "TDoAAnchorRangingApplication.h"
#include "RangingHost.h"
#include "Utilities.h"
#include "RangingHost.h"
#include "HardwareClockClient.h"
#include "HardwareClock.h"

using namespace inet;
using namespace inet::physicallayer;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(TDoAAnchorRangingApplication);

void
TDoAAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& broadcastBeaconDelayParamater = par ("broadcastBeaconDelay");
        assert (broadcastBeaconDelayParamater.getType () == cPar::LONG);
        broadcastBeaconDelay = SimTime {broadcastBeaconDelayParamater.longValue (), SIMTIME_PS};

        const auto& echoBeaconDelayParamater = par ("echoBeaconDelay");
        assert (echoBeaconDelayParamater.getType () == cPar::LONG);
        echoBeaconDelay = SimTime {echoBeaconDelayParamater.longValue (), SIMTIME_PS};

        const auto& echoAnchorAddressParamater = par ("echoAnchorAddress");
        assert (echoAnchorAddressParamater.getType () == cPar::STRING);
        const auto macAddess = echoAnchorAddressParamater.stdstringValue ();
        if (!macAddess.empty ()) {
            echoAnchorAddress.setAddress (echoAnchorAddressParamater.stdstringValue ().c_str ());
        }

        auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        rangingHost->addRxStateChangedCallback ([this] (IRadio::ReceptionState state) { this->onRxStateChangedCallback (state); });

        if (broadcastBeaconDelay > 0)
        {
            unique_ptr<cMessage> message {new cMessage {"sendNextBeacon"}};
            scheduleSelfMessage (move (message), broadcastBeaconDelay);
        }
    }
}

void
TDoAAnchorRangingApplication::finish ()
{
    RangingApplication::finish ();
}

void
TDoAAnchorRangingApplication::handleMessage (cMessage* message)
{
    unique_ptr<cMessage> messageHandler {message};

    if (message->isSelfMessage ())
    {
        handleSelfMessage ();
    }
    else
    {
        handlFrame (check_and_cast<BeaconFrame*> (message));
    }
}

void
TDoAAnchorRangingApplication::handlFrame (BeaconFrame* frame)
{
    const auto packetControlInformation = check_and_cast<const Ieee802Ctrl*> (frame->getControlInfo ());
    const auto sourceAddress = packetControlInformation->getSourceAddress ();

    if (sourceAddress == echoAnchorAddress)
    {
        // Compute delay
        SimTime delay {echoBeaconDelay - (getHWtime () - beaconReceptionTimestamp)};
        EXPECT (delay > 0, "Cannot send MAC packet with negative delay");

        unique_ptr<cMessage> message {new cMessage {"sendBeaconMessage"}};
        scheduleSelfMessage (move (message), delay);
    }
}

void
TDoAAnchorRangingApplication::handleSelfMessage ()
{
    sendBeaconFrame ();

    if (broadcastBeaconDelay > 0)
    {
        unique_ptr<cMessage> message {new cMessage {"sendBeaconMessage"}};
        scheduleSelfMessage (move (message), broadcastBeaconDelay);
    }
}

unsigned int
TDoAAnchorRangingApplication::getCurrentPacketSequenceNumber () const
{
    return packetSequenceNumberGenerator;
}

unsigned int
TDoAAnchorRangingApplication::getNextPacketSequenceNumber ()
{
    return ++packetSequenceNumberGenerator;
}

void
TDoAAnchorRangingApplication::sendBeaconFrame ()
{
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());

    // Prepare & send beacon
    unique_ptr<BeaconFrame> frame {new BeaconFrame {}};

    frame->setBitLength (10);
    frame->setSequenceNumber (getNextPacketSequenceNumber ());
    frame->setPosition (rangingHost->getCurrentPosition ());

    sendFrame (MACAddress::BROADCAST_ADDRESS, unique_ptr<Frame> (frame.release ()), 0);
}

void
TDoAAnchorRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)    {
        beaconReceptionTimestamp = getHWtime ();
    }
}

}; // namespace ipin2017
