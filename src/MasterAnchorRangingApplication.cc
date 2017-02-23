#include <cassert>
#include <memory>
#include <algorithm>

#include <INETDefs.h>
#include <MasterAnchorRangingApplication.h>
#include <MACAddress.h>
#include <IdealMacFrame_m.h>
#include <Ieee802Ctrl.h>

#include "RangingHost.h"
#include "Utilities.h"
#include "RangingHost.h"

using namespace inet;
using namespace inet::physicallayer;
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

        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        rangingHost->addTxStateChangedCallback ([this] (IRadio::TransmissionState state) { this->onTxStateChangedCallback (state); });
        rangingHost->addRxStateChangedCallback ([this] (IRadio::ReceptionState state) { this->onRxStateChangedCallback (state); });
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
            handleBackhaulMessage (check_and_cast<BackhaulMessage*> (message));
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
        default:
            throw cRuntimeError ("Unsupported self message");
    }
}

void
MasterAnchorRangingApplication::handleFrame (RangingReplyFrame* frame)
{
    EXPECT (frame->getSequenceNumber () == getCurrentPacketSequenceNumber () + 1, "Invalid ranging reply received");

    const auto beacon = find_if (beacons.rbegin (), beacons.rend (), [frame] (const Beacon& element) {
        return element.sequenceNumber == frame->getSequenceNumber ()  - 1;
    });

    EXPECT (!(beacon == beacons.rend ()), "Invalid ranging reply received");

    const auto packetControlInformation = check_and_cast<const Ieee802Ctrl*> (frame->getControlInfo ());

    const auto mobileReply = find_if (beacon->mobileReplies.rbegin (), beacon->mobileReplies.rend (), [packetControlInformation] (const MobileReply& element) {
        return element.mobileAddress == packetControlInformation->getSourceAddress ();
    });

    mobileReply->receptionTimestamp = frameReceptionTimestamp;

    EV << "Ranging reply received from " << mobileReply->mobileAddress.str () << " at " << mobileReply->receptionTimestamp << endl;
}

void
MasterAnchorRangingApplication::handleBackhaulMessage (const BackhaulMessage* message)
{
    const auto frame = check_and_cast<const Frame*> (message->getFrame ());
    switch (frame->getType ())
    {
        case RANGING_REPLY_FRAME:
            handleBackhaulMessage (message, check_and_cast<const RangingReplyFrame*> (frame));
            break;
        case BEACON_FRAME:
            handleBackhaulMessage (message, check_and_cast<const BeaconFrame*> (frame));
            break;
    }
}

void
MasterAnchorRangingApplication::handleBackhaulMessage (const BackhaulMessage* message,
                                                       const RangingReplyFrame* frame)
{
    const auto beacon = find_if (beacons.rbegin (), beacons.rend (), [frame] (const Beacon& element) {
        return element.sequenceNumber == frame->getSequenceNumber ()  - 1;
    });

    EXPECT (!(beacon == beacons.rend ()), "Invalid ranging reply received on backhaul");

    auto mobileReply = find_if (beacon->mobileReplies.rbegin (), beacon->mobileReplies.rend (), [message] (const MobileReply& element) {
        return element.mobileAddress == message->getFrameSourceAddress ();
    });

    if (mobileReply == beacon->mobileReplies.rend ())
    {
        MobileReply dummyMobileReply;
        dummyMobileReply.mobileAddress = message->getFrameSourceAddress ();
        dummyMobileReply.mobileRealPosition = frame->getRealPosition ();
        beacon->mobileReplies.emplace_back (move (dummyMobileReply));

        mobileReply = find_if (beacon->mobileReplies.rbegin (), beacon->mobileReplies.rend (), [message] (const MobileReply& element) {
            return element.mobileAddress == message->getFrameSourceAddress ();
        });
    }

    MobileReplyEcho mobileReplyEcho;
    mobileReplyEcho.receptionTimestamp = message->getReceptionTimestamp ();
    mobileReplyEcho.helperAnchorAddress = message->getHelperAnchorAddress ();
    mobileReplyEcho.helperAnchorPosition = message->getPosition ();

    EXPECT (!(mobileReply == beacon->mobileReplies.rend ()), "Invalid ranging reply received on backhaul");

    EV << "Ranging reply echo received from " << mobileReplyEcho.helperAnchorAddress.str () << " at " << mobileReplyEcho.receptionTimestamp << endl;

    mobileReply->echos.emplace_back (move (mobileReplyEcho));
}

void
MasterAnchorRangingApplication::handleBackhaulMessage (const BackhaulMessage* message,
                                                       const BeaconFrame* frame)
{
    const auto beacon = find_if (beacons.rbegin (), beacons.rend (), [frame] (const Beacon& element) {
        return frame->getSequenceNumber () == element.sequenceNumber;
    });

    EXPECT (!(beacon == beacons.rend ()), "Invalid beacon received on backhaul");

    BeaconEcho beaconEcho;
    beaconEcho.receptionTimestamp = message->getReceptionTimestamp ();
    beaconEcho.helperAnchorAddress = message->getHelperAnchorAddress ();
    beaconEcho.helperAnchorPosition = message->getPosition ();

    EV << "Beacon echo received from " << beaconEcho.helperAnchorAddress.str () << " at " << beaconEcho.receptionTimestamp << endl;

    beacon->beaconEchos.push_back (move (beaconEcho));
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

void
MasterAnchorRangingApplication::onTxStateChangedCallback (IRadio::TransmissionState state)
{
    if (state == IRadio::TRANSMISSION_STATE_TRANSMITTING)
    {
        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        const auto radio = check_and_cast<IRadio*> (rangingHost->getModuleByPath (".nic.radio"));
        const auto transmission = radio->getTransmissionInProgress ();
        const auto macFrame = check_and_cast<const IdealMacFrame*> (transmission->getMacFrame ());
        EXPECT (macFrame->getSrc () == rangingHost->getLocalAddress (), "Transmitted frame is not a beacon");
        EXPECT (macFrame->getDest () == MACAddress (MACAddress::BROADCAST_ADDRESS), "Transmitted frame is not a beacon");

        const auto frame = check_and_cast<const Frame*> (macFrame->getEncapsulatedPacket ());
        EXPECT (frame->getSequenceNumber () == getCurrentPacketSequenceNumber (), "Transmitted frame is not a valid beacon");

        Beacon beacon;
        beacon.transmissionTimestamp = simTime ();
        beacon.masterAnchorAddress = rangingHost->getLocalAddress ();
        beacon.masterAnchorPosition = rangingHost->getCurrentPosition ();
        beacon.sequenceNumber = frame->getSequenceNumber ();

        EV << "Beacon seq. no. " << beacon.sequenceNumber << " sent at" << beacon.transmissionTimestamp << endl;

        beacons.emplace_back (move (beacon));
    }
}

void
MasterAnchorRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)    {
        frameReceptionTimestamp = simTime ();
    }
}

}; // namespace ipin2017
