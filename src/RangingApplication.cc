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

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>

#include "RangingApplication.h"
#include "RangingHost.h"
#include "HardwareClock.h"
#include "Frame_m.h"

using namespace omnetpp;
using namespace inet;
using namespace inet::physicallayer;
using namespace std;

namespace ipin2017
{

Define_Module(RangingApplication);

void
RangingApplication::initialize (int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        setHardwareClock(HardwareClock::findFirstClock(getParentModule()));
    }
}

void
RangingApplication::sendFrame (const inet::MACAddress& destinationAddress,
                               unique_ptr<Frame> frame,
                               const SimTime& delay)
{
    assert (frame);
    auto ranginghHst = check_and_cast<RangingHost*> (getParentModule ());
    auto controlInformation = unique_ptr<Ieee802Ctrl> {new Ieee802Ctrl};
    controlInformation->setSourceAddress (ranginghHst->getLocalAddress ());
    controlInformation->setDest (destinationAddress);
    frame->setControlInfo (controlInformation.release ());
    sendDelayed (frame.release (), delay, "out");
}

void
RangingApplication::scheduleSelfMessage (unique_ptr<cMessage> message,
                                         const SimTime& delay)
{
    const auto timestamp = getHWtime () + delay;
    scheduleAtHWtime (timestamp, message.release ());
}

int
RangingApplication::numInitStages () const
{
    return NUM_INIT_STAGES;
}

} //namespace ipin2017
