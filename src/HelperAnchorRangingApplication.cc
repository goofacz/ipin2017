#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <HelperAnchorRangingApplication.h>
#include <MACAddress.h>


using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(HelperAnchorRangingApplication);

void
HelperAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void
HelperAnchorRangingApplication::handleMessage (cMessage* message)
{
    // TODO
}

}; // namespace ipin2017
