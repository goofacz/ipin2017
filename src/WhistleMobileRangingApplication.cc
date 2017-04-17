#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

#include <INETDefs.h>
#include <Ieee802Ctrl.h>
#include <IdealMacFrame_m.h>

#include "WhistleMobileRangingApplication.h"
#include "RangingHost.h"
#include "WhistleFrame_m.h"

using namespace inet;
using namespace inet::physicallayer;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(WhistleMobileRangingApplication);

void
WhistleMobileRangingApplication::initialize (int stage)
{
    RangingApplication::initialize (stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& frameTransmissionIntervalParamater = par ("frameTransmissionInterval");
        assert (frameTransmissionIntervalParamater.getType () == cPar::LONG);
        frameTransmissionInterval = SimTime {frameTransmissionIntervalParamater.longValue (), SIMTIME_PS};

        auto frameTransmitMessage = new cMessage ("frameTransmitMessage");
        scheduleAt (simTime () + frameTransmissionInterval, frameTransmitMessage);
    }
}

void
WhistleMobileRangingApplication::handleMessage (cMessage* message)
{
    unique_ptr<cMessage> messageHandler {message};

    if (message->isSelfMessage ())
    {
        // Send frame
        unique_ptr<WhistleFrame> frame {new WhistleFrame {}};
        frame->setBitLength (10);
        frame->setSequenceNumber (getNextPacketSequenceNumber ());
        sendFrame (MACAddress::BROADCAST_ADDRESS, unique_ptr<Frame> (frame.release ()), 0);

        // Schedule next frame
        auto frameTransmitMessage = new cMessage ("frameTransmitMessage");
        scheduleAt (simTime () + frameTransmissionInterval, frameTransmitMessage);
    }
}

unsigned int
WhistleMobileRangingApplication::getNextPacketSequenceNumber ()
{
    return ++packetSequenceNumberGenerator;
}

}; // namespace ipin2017
