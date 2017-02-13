#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>
#include <MACFrameBase_m.h>

#include "RangingApplication.h"

using namespace omnetpp;
using namespace inet;

namespace ipin2017
{

Define_Module(RangingApplication);

void RangingApplication::initialize (int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

} //namespace ipin2017
