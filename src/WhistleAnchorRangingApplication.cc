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
    }
}

void
WhistleAnchorRangingApplication::finish ()
{
    auto ranginghHst = check_and_cast<RangingHost*> (getParentModule ());
    ofstream resultFile;
    resultFile.open ("whistle_simulation_result", ios_base::out | ios_base::app);

    for (const auto& entry : recordedFrames)
    {
        resultFile << ranginghHst->getLocalAddress ().getInt () << ',';
        resultFile << entry.frame->getEchoFrame () << ',';
        resultFile << entry.frame->getSequenceNumber () << ',';
        resultFile << entry.receptionTimestamp.inUnit (SIMTIME_PS) << ',';
        resultFile << entry.transmissionTimestamp.inUnit (SIMTIME_PS) << ',';
        resultFile << entry.position.x << ',';
        resultFile << entry.position.y << '\n';
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
WhistleAnchorRangingApplication::handleSelfMessage (cMessage* message)
{
    assert (scheduledEchoFrame);
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    recordedFrames.emplace_back (unique_ptr<const WhistleFrame> {scheduledEchoFrame->dup ()}, getHWtime (), getHWtime (), rangingHost->getCurrentPosition ());
    sendFrame (MACAddress::BROADCAST_ADDRESS, unique_ptr<Frame> (scheduledEchoFrame.release ()), 0);
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
    recordedFrames.emplace_back (unique_ptr<const WhistleFrame> (frame->dup ()), frameReceptionTimestamp, 0, rangingHost->getCurrentPosition ());
    frameReceptionTimestamp = 0;
}

WhistleAnchorRangingApplication::RecordedFrame::RecordedFrame (unique_ptr<const WhistleFrame> frame,
                                                               const SimTime& receptionTimestamp,
                                                               const SimTime& transmissionTimestamp,
                                                               Coord position) :
    frame {move (frame)},
    receptionTimestamp {receptionTimestamp},
    transmissionTimestamp {transmissionTimestamp},
    position {move (position)}
{
    // ...
}

}; // namespace ipin2017
