#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

#include <INETDefs.h>
#include <Ieee802Ctrl.h>
#include <IdealMacFrame_m.h>

#include "WhistleAnchorRangingApplication.h"
#include "RangingHost.h"

using namespace inet;
using namespace inet::physicallayer;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(WhistleAnchorRangingApplication);

void
WhistleAnchorRangingApplication::initialize (int stage)
{
    RangingApplication::initialize (stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& isBaseAnchorParameter = par ("isBaseAnchor");
        assert (isBaseAnchorParameter.getType () == cPar::BOOL);
        isBaseAnchor = isBaseAnchorParameter.boolValue ();

        const auto& echoFrameDelayParameter = par ("echoFrameDelay");
        assert (echoFrameDelayParameter.getType () == cPar::LONG);
        echoFrameDelay = SimTime (echoFrameDelayParameter.longValue (), SIMTIME_PS);

        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        rangingHost->addRxStateChangedCallback ([this] (IRadio::ReceptionState state) { this->onRxStateChangedCallback (state); });
        rangingHost->addTxStateChangedCallback ([this] (IRadio::TransmissionState state) { this->onTxStateChangedCallback (state); });
    }
}

void
WhistleAnchorRangingApplication::finish ()
{
    const auto& resultsFileNameParameter = par ("resultsFileName");
    assert (resultsFileNameParameter.getType () == cPar::STRING);
    assert (resultsFileNameParameter.stdstringValue () != "");

    ofstream resultFile;
    resultFile.open (resultsFileNameParameter.stringValue (), ios_base::out | ios_base::app);

    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    for (const auto& entry : recordedFrames)
    {
        resultFile << rangingHost->getLocalAddress ().getInt () << ',';
        resultFile << entry.frame->getEchoFrame () << ',';
        resultFile << entry.frame->getSequenceNumber () << ',';
        resultFile << entry.receptionTimestamp.inUnit (SIMTIME_PS) << ',';
        resultFile << entry.transmissionTimestamp.inUnit (SIMTIME_PS) << ',';
        resultFile << entry.anchorPosition.x << ',';
        resultFile << entry.anchorPosition.y << ',';
        resultFile << entry.mobilePosition.x << ',';
        resultFile << entry.mobilePosition.y << '\n';
    }

    resultFile.flush ();
}

void
WhistleAnchorRangingApplication::handleMessage (cMessage* message)
{
    unique_ptr<cMessage> messageHandler {message};

    if (message->isSelfMessage ())
    {
        assert (isBaseAnchor);
        handleSelfMessage (message);
    }
    else
    {
        const auto frame = check_and_cast<Frame*> (message);
        switch (frame->getType())
        {
            case FrameType::WHISTLE_FRAME:
                handleMessage (check_and_cast<WhistleFrame*> (message));
                break;
        }
    }
}

void
WhistleAnchorRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)
    {
        assert (frameReceptionTimestamp == 0);
        frameReceptionTimestamp = getHWtime ();
    }
}

void
WhistleAnchorRangingApplication::onTxStateChangedCallback (IRadio::TransmissionState state)
{
    if (state == IRadio::TRANSMISSION_STATE_TRANSMITTING)
    {
        const auto mobileRangingHost = check_and_cast<RangingHost*> (getSimulation ()->getModuleByPath ("Mobile1"));
        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        recordedFrames.emplace_back (unique_ptr<const WhistleFrame> {scheduledEchoFrame.release ()}, getHWtime (), getHWtime (), rangingHost->getCurrentPosition (), mobileRangingHost->getCurrentPosition ());
    }
}

void
WhistleAnchorRangingApplication::handleSelfMessage (cMessage* message)
{
    assert (scheduledEchoFrame);
    sendFrame (MACAddress::BROADCAST_ADDRESS, unique_ptr<Frame> (scheduledEchoFrame->dup ()), 0);
}

void
WhistleAnchorRangingApplication::handleMessage (const WhistleFrame* frame)
{
    assert (frameReceptionTimestamp > 0);
    if (isBaseAnchor && !frame->getEchoFrame ())
    {
        assert (!scheduledEchoFrame);
        scheduledEchoFrame.reset (new WhistleFrame {});
        scheduledEchoFrame->setBitLength (10);
        scheduledEchoFrame->setSequenceNumber (frame->getSequenceNumber ());
        scheduledEchoFrame->setEchoFrame (true);

        unique_ptr<cMessage> sendEchoFrameMessage {new cMessage ("sendEchoFrameMessage")};
        scheduleAtHWtime (frameReceptionTimestamp + echoFrameDelay, sendEchoFrameMessage.release ());
    }

    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    const auto mobileRangingHost = check_and_cast<RangingHost*> (getSimulation ()->getModuleByPath ("Mobile1"));
    recordedFrames.emplace_back (unique_ptr<const WhistleFrame> (frame->dup ()), frameReceptionTimestamp, 0, rangingHost->getCurrentPosition (), mobileRangingHost->getCurrentPosition ());
    frameReceptionTimestamp = 0;
}

WhistleAnchorRangingApplication::RecordedFrame::RecordedFrame (unique_ptr<const WhistleFrame> frame,
                                                               const SimTime& receptionTimestamp,
                                                               const SimTime& transmissionTimestamp,
                                                               const Coord& anchorPosition,
                                                               const Coord& mobilePosition) :
    frame {move (frame)},
    receptionTimestamp {receptionTimestamp},
    transmissionTimestamp {transmissionTimestamp},
    anchorPosition {anchorPosition},
    mobilePosition {mobilePosition}
{
    // ...
}

}; // namespace ipin2017
