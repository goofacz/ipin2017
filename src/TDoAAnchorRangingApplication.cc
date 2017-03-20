#include <cassert>
#include <memory>
#include <algorithm>
#include <fstream>

#include <INETDefs.h>
#include <TDoAAnchorRangingApplication.h>
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

Define_Module(TDoAAnchorRangingApplication);

void
TDoAAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void
TDoAAnchorRangingApplication::finish ()
{
    RangingApplication::finish ();
}

void
TDoAAnchorRangingApplication::handleMessage (cMessage* message)
{
    // TODO
    delete message;
}

}; // namespace ipin2017
