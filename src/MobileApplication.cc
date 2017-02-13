//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <iostream>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>
#include <MACFrameBase_m.h>

#include "src/MobileApplication.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017 {

Define_Module(MobileApplication);

void MobileApplication::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        if (par("sendMsgOnInit").boolValue() == true)
        {
            MACFrameBase *msg = new MACFrameBase();
            msg->setByteLength(16);
            msg->setDestAddr(MACAddress ("0A-AA-00-00-00-02"));
            Ieee802Ctrl* ctrl = new Ieee802Ctrl();
            ctrl->setDest(MACAddress ("0A-AA-00-00-00-02"));
            msg->setControlInfo(ctrl);
            send (msg, gate ("out"));
        }
    }
}

void MobileApplication::handleMessage(cMessage *msg)
{
    // just send back the message we received
    EV << "Badum!~!!!!!!!!!!!!";
}

int MobileApplication::numInitStages() const
{
    return NUM_INIT_STAGES;
}

}; // namespace
