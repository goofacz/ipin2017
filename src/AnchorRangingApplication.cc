#include <iostream>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>
#include <MACFrameBase_m.h>

#include "AnchorRangingApplication.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(AnchorRangingApplication);

void AnchorRangingApplication::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void AnchorRangingApplication::handleMessage(cMessage *msg)
{
    // TODO
}

int AnchorRangingApplication::numInitStages() const
{
    return NUM_INIT_STAGES;
}

}; // namespace ipin2017
