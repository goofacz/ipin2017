/*   IPIN 2017 Localization Method Simulator
 *
 *   Copyright (C) 2017 Tomasz Jankowski
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

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
