#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

#include <INETDefs.h>
#include <Ieee802Ctrl.h>
#include <IdealMacFrame_m.h>

#include "WhistleBaseAnchorRangingApplication.h"
#include "RangingHost.h"
#include "WhistleFrame_m.h"

using namespace inet;
using namespace inet::physicallayer;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(WhistleBaseAnchorRangingApplication);

void
WhistleBaseAnchorRangingApplication::initialize (int stage)
{
    RangingApplication::initialize (stage);
}

void
WhistleBaseAnchorRangingApplication::finish ()
{
    // ...
}

void
WhistleBaseAnchorRangingApplication::handleMessage (cMessage* message)
{
    // ...
}

}; // namespace ipin2017
