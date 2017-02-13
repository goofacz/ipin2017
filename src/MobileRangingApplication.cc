#include <iostream>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>
#include <MACFrameBase_m.h>

#include "MobileRangingApplication.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(MobileRangingApplication);

void MobileRangingApplication::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void MobileRangingApplication::handleMessage(cMessage *msg)
{
    // TODO
}

int MobileRangingApplication::numInitStages() const
{
    return NUM_INIT_STAGES;
}

}; // namespace ipin2017
